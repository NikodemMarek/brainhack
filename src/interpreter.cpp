#include "interpreter.h"
#include <cstdio>
#include <iostream>
#include <ostream>

Interpreter::Interpreter(Tape &&tape, Memory &memory, IO &io)
    : tape(tape), memory(memory), io(io) {}

bool Interpreter::next() {
  std::optional<Operation> operation = tape.next();
  if (!operation.has_value()) {
    return false;
  }

  int count = operation.value().count;
  switch (operation.value().op) {
  case Operator::INCREMENT:
    memory.change(count);
    break;
  case Operator::DECREMENT:
    memory.change(-count);
    break;

  case Operator::RIGHT:
    memory.move(count);
    break;
  case Operator::LEFT:
    memory.move(-count);
    break;

  case Operator::OUTPUT:
    output_memory(count);
    break;
  case Operator::INPUT:
    input_memory(count);
    break;

  case Operator::FORWARD:
    this->branch_forward();
    break;
  case Operator::BACKWARD:
    this->branch_backwards();
    break;
  }

  return true;
}

void Interpreter::output_memory(int count) {
  char out = static_cast<char>(memory.get());
  io.output(out, count);
}
void Interpreter::input_memory(int count) {
  char input = io.input(count);
  memory.set(static_cast<int>(input));
}

void Interpreter::branch_forward() {
  std::optional<int> pair = tape.get_pair(tape.get_position() - 1);
  if (!pair.has_value()) {
    std::cerr << "Error: No matching ] bracket found." << std::endl;
  }

  if (memory.get() == 0) {
    tape.branch(pair.value() + 1);
  }
}
void Interpreter::branch_backwards() {
  std::optional<int> pair = tape.get_pair(tape.get_position() - 1);
  if (!pair.has_value()) {
    std::cerr << "Error: No matching [ bracket found." << std::endl;
  }

  if (memory.get() != 0) {
    tape.branch(pair.value() + 1);
  }
}
