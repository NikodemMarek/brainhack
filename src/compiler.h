#ifndef COMPILER_H
#define COMPILER_H

#include "tape.h"
#include <string>

class Compiler {
public:
  Compiler(Tape &&tape);

  std::optional<std::string> next();

private:
  Tape tape;
};

#endif
