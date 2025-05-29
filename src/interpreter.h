#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "io.h"
#include "memory.h"
#include "tape.h"
#include <vector>

class Interpreter {
public:
  Interpreter(Tape &tape, Memory &memory, IO &io);

  bool next();

private:
  Tape &tape;
  Memory &memory;
  IO &io;

  void output_memory(const int count) const;
  void input_memory(const int count);

  void branch_forward();
  void branch_backwards();
};

#endif
