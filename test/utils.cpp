#include "utils.h"
#include "../src/interpreter.cpp"
#include "../src/memory.cpp"
#include "../src/parser.cpp"
#include "../src/tape.cpp"

TestIO::TestIO(std::string input) : output_buffer(""), input_buffer(input) {}

void TestIO::output(char c, int count) {
  for (int i = 0; i < count; i++) {
    output_buffer += c;
  }
}
char TestIO::input(int count) {
  char c = input_buffer.at(count - 1);
  input_buffer.erase(0, count);
  return c;
}

bool TestIO::is_at_val(const int at, const int expected) {
  return static_cast<int>(output_buffer[at]) == expected;
}

bool operator==(const Operation &lhs, const Operation &rhs) {
  return lhs.op == rhs.op && lhs.count == rhs.count;
}

std::vector<Operation> test_parse(std::string input) {
  return parse(input, test_operation_parser);
}
std::optional<Operator> test_operation_parser(char c) {
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

Tape test_tape(std::string input) {
  return Tape(parse(input, test_operation_parser));
}

Memory test_memory() {
  Memory memory;
  return memory;
}

TestIO test_io(std::string input) { return TestIO(input); }

Interpreter test_interpreter(Tape &tape, Memory &memory, IO &io) {
  return Interpreter(tape, memory, io);
}

std::string TestAssembly::prologue() const {
  return "bf_tape declaration\nstart function definition\n";
}
std::string TestAssembly::epilogue() const {
  return "call to end the program\n";
}
std::string TestAssembly::operation(const Tape &tape,
                                    const Operation &operation) const {
  int count = operation.count;
  switch (operation.op) {
  case Operator::INCREMENT:
    return "increment " + std::to_string(count) + "\n";
  case Operator::DECREMENT:
    return "decrement " + std::to_string(count) + "\n";
  case Operator::RIGHT:
    return "right " + std::to_string(count) + "\n";
  case Operator::LEFT:
    return "left " + std::to_string(count) + "\n";
  case Operator::OUTPUT:
    return "output " + std::to_string(count) + "\n";
  case Operator::INPUT:
    return "input " + std::to_string(count) + "\n";
  case Operator::FORWARD:
    return "forward\n";
  case Operator::BACKWARD:
    return "backward\n";
  }
  return "";
}

Compiler<TestAssembly> test_compiler(Tape &tape) {
  return Compiler<TestAssembly>(std::move(tape), TestAssembly());
}
