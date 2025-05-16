#include "interpreter.h"
#include "parser.h"
#include "stdio.h"
#include <cstdio>
#include <functional>
#include <iostream>
#include <ostream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " <file.bf>" << std::endl;
    return 1;
  }

  std::string filename = argv[1];

  auto parsed = parse_file(filename, parse_operation);
  Tape tape(parsed);
  Memory memory;
  StdIO io;
  Interpreter interpreter(std::move(tape), memory, io);

  while (interpreter.next()) {
  }
  return 0;
}
