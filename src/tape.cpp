#include "tape.h"

Tape::Tape(std::vector<Operation> input) : position(0), input(input) {}

std::optional<Operation> Tape::next() {
  if (this->position >= this->input.size()) {
    return std::nullopt;
  }
  return this->input.at(this->position++);
}
std::optional<Operation> Tape::at(int position) {
  return this->input.at(position);
}

std::optional<int> Tape::get_pair(int start) {
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
      this->brackets[start] = end;
      this->brackets[end] = start;
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

void Tape::branch(int to) { position = to; }

int Tape::get_position() { return this->position; }
