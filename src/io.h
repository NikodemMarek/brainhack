#ifndef IO_H
#define IO_H

class IO {
public:
  virtual void output(char c, int count) = 0;
  virtual char input(int count) = 0;
};

#endif
