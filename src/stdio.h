#ifndef STDIO_H
#define STDIO_H

#include "io.h"

class StdIO : public IO {
public:
  virtual void output(char c, int count) override;
  virtual char input(int count) override;
};

#endif
