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

  std::vector<int> get_range(const int start, const int end) const;

  std::string print_range() const;
  int pointer() const;
};

class DebugIO : public IO {
public:
  DebugIO();

  virtual void output(const char c, const int count) override;
  virtual char input(const int count) override;

  std::string get_output() const;

private:
  std::string output_buffer;
};

class Debugger {
public:
  Debugger(Tape &tape);

  bool next();

  std::string print_state() const;

private:
  Tape &tape;
  DebuggerMemory memory;
  DebugIO io;
  Interpreter interpreter;
};

#endif
