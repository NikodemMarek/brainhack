#ifndef UTILS_H
#define UTILS_H

#include "../src/interpreter.h"
#include "../src/memory.h"
#include "../src/operation.h"
#include "../src/tape.h"
#include <functional>
#include <optional>
#include <string>

class TestIO : public IO {
public:
  std::string output_buffer;
  std::string input_buffer;

  TestIO(std::string input = "");

  virtual void output(char c, int count) override;
  virtual char input(int count) override;

  bool is_at_val(const int at, const int expected);
};

bool operator==(const Operation &lhs, const Operation &rhs);

std::vector<Operation> test_parse(std::string input);
std::optional<Operator> test_operation_parser(char c);

Tape test_tape(std::string input);

Memory test_memory();

TestIO test_io(std::string input = "");

Interpreter test_interpreter(std::string input, Memory &memory, IO &io);

#endif
