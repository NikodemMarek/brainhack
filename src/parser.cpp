#include "parser.h"
#include "operation.h"
#include <fstream>
#include <functional>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

std::tuple<std::optional<Operation>, std::optional<Operation>>
combine(Operation a, Operation b) {
  if (a.op == Operator::FORWARD || a.op == Operator::BACKWARD ||
      b.op == Operator::FORWARD || b.op == Operator::BACKWARD) {
    return {a, b};
  }

  if (a.op == b.op) {
    return {Operation{a.op, a.count + b.count}, std::nullopt};
  }

  if (a.op == Operator::INCREMENT && b.op == Operator::DECREMENT ||
      a.op == Operator::DECREMENT && b.op == Operator::INCREMENT) {
    if (a.op == Operator::DECREMENT) {
      std::swap(a, b);
    }

    if (a.count > b.count) {
      return {Operation{Operator::INCREMENT, a.count - b.count}, std::nullopt};
    } else if (a.count < b.count) {
      return {Operation{Operator::DECREMENT, b.count - a.count}, std::nullopt};
    } else {
      return {std::nullopt, std::nullopt};
    }
  }

  if (a.op == Operator::RIGHT && b.op == Operator::LEFT ||
      a.op == Operator::LEFT && b.op == Operator::RIGHT) {
    if (a.op == Operator::LEFT) {
      std::swap(a, b);
    }

    if (a.count > b.count) {
      return {Operation{Operator::RIGHT, a.count - b.count}, std::nullopt};
    } else if (a.count < b.count) {
      return {Operation{Operator::LEFT, b.count - a.count}, std::nullopt};
    } else {
      return {std::nullopt, std::nullopt};
    }
  }

  return {a, b};
}

std::vector<Operation>
parse(std::string input, std::function<std::optional<Operator>(char)> parser) {
  std::vector<Operation> operations;
  std::optional<Operation> current = std::nullopt;
  for (char c : input) {
    auto op = parser(c);
    if (!op.has_value()) {
      continue;
    }

    if (!current.has_value()) {
      current = Operation{op.value(), 1};
      continue;
    }

    std::optional<Operation> merged_op;
    std::optional<Operation> new_op;
    std::tie(merged_op, new_op) =
        combine(current.value(), Operation{op.value(), 1});

    if (new_op.has_value()) {
      operations.push_back(merged_op.value());
      current = new_op;
    } else {
      current = merged_op;
    }
  }

  if (current.has_value()) {
    operations.push_back(current.value());
  }

  return operations;
}

std::optional<Operator> parse_operation(char c) {
  switch (c) {
  case '+':
    return Operator::INCREMENT;
  case '-':
    return Operator::DECREMENT;
  case '>':
    return Operator::RIGHT;
  case '<':
    return Operator::LEFT;
  case '.':
    return Operator::OUTPUT;
  case ',':
    return Operator::INPUT;
  case '[':
    return Operator::FORWARD;
  case ']':
    return Operator::BACKWARD;
  default:
    return std::nullopt;
  }
}

std::vector<Operation>
parse_file(const std::string &path,
           std::function<std::optional<Operator>(char)> parser) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file at " + path);
  }

  std::string str;
  std::vector<Operation> operations;
  while (std::getline(file, str)) {
    std::vector<Operation> parsed = parse(str, parser);
    if (parsed.empty()) {
      continue;
    }

    if (operations.empty()) {
      operations.insert(operations.end(),
                        std::make_move_iterator(parsed.begin()),
                        std::make_move_iterator(parsed.end()));
      continue;
    }

    Operation last = std::move(operations.back());
    operations.pop_back();
    Operation first = std::move(parsed.front());
    parsed.erase(parsed.begin());

    std::optional<Operation> combined_first;
    std::optional<Operation> combined_second;
    std::tie(combined_first, combined_second) = combine(last, first);

    if (combined_first.has_value()) {
      operations.push_back(combined_first.value());
    }
    if (combined_second.has_value()) {
      operations.push_back(combined_second.value());
    }
    operations.insert(operations.end(), std::make_move_iterator(parsed.begin()),
                      std::make_move_iterator(parsed.end()));
  }

  return operations;
}
