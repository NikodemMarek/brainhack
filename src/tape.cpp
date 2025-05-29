#include "tape.h"

Tape::Tape(std::vector<Operation> input) : position(0), input(input) {
  brackets = std::map<int, int>();

  for (int i = 0; i < input.size(); i++) {
    if (input[i].op == Operator::FORWARD) {
      std::optional<int> pair = this->get_pair(i);
      if (pair.has_value()) {
        brackets[i] = pair.value();
        brackets[pair.value()] = i;
      }
    }
  }
}

std::optional<Operation> Tape::at(const int position) const {
  return this->input.at(position);
}
std::optional<Operation> Tape::next() {
  if (this->position >= this->input.size()) {
    return std::nullopt;
  }
  return this->input.at(this->position++);
}
std::optional<Operation> Tape::peek() const {
  if (this->position >= this->input.size()) {
    return std::nullopt;
  }
  return this->input.at(this->position);
}

std::optional<int> Tape::get_pair(const int start) const {
  if (start < 0 || start >= this->input.size()) {
    return std::nullopt;
  }

  if (this->at(start)->op != Operator::FORWARD &&
      this->at(start)->op != Operator::BACKWARD) {
    return std::nullopt;
  }

  auto pair = this->brackets.find(start);
  if (pair != this->brackets.end()) {
    return std::optional(pair->second);
  }
  if (this->at(start)->op == Operator::BACKWARD) {
    return std::nullopt;
  }

  int end = start + 1;
  while (end < this->input.size()) {
    if (this->at(end)->op == Operator::BACKWARD) {
      return std::optional(end);
    }

    if (this->at(end)->op == Operator::FORWARD) {
      std::optional<int> pair = this->get_pair(end);
      if (!pair.has_value()) {
        return std::nullopt;
      }
      end = pair.value();
    }

    end++;
  }

  return std::nullopt;
}

void Tape::branch(const int to) { position = to; }

int Tape::get_position() const { return this->position; }
