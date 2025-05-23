#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "interpreter.h"
#include "io.h"
#include "memory.h"
#include "tape.h"
#include <string>
#include <vector>

class DebuggerMemory : public Memory {
public:
  DebuggerMemory();

  std::vector<int> get_range(int start, int end);

  std::string print_range();
  int pointer();
};

class DebugIO : public IO {
public:
  DebugIO();

  virtual void output(char c, int count) override;
  virtual char input(int count) override;

  std::string get_output();

private:
  std::string output_buffer;
};

class Debugger {
public:
  Debugger(Tape &tape);

  bool next();

  std::string print_state();

private:
  Tape &tape;
  DebuggerMemory memory;
  DebugIO io;
  Interpreter interpreter;
};

#endif
