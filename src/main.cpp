#include "interpreter.h"
#include "parser.h"
#include "stdio.h"
#include <cstdio>
#include <functional>

int main() {
  std::string hello_world = ">+++++++++[<++++++++>-]<.>+++++++[<++++>-]<+.+++++"
                            "++..+++.[-]>++++++++[<++++>-]"
                            "<.>+++++++++++[<++++++++>-]<-.--------.+++.------."
                            "--------.[-]>++++++++[<++++>-]<+.[-]++++++++++.";
  auto parsed = parse(hello_world, parse_operation);
  Tape tape(parsed);
  Memory memory;
  StdIO io;
  Interpreter interpreter(std::move(tape), memory, io);

  while (interpreter.next()) {
  }
  return 0;
}
