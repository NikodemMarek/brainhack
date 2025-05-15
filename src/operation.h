#ifndef OPERATION_H
#define OPERATION_H

enum Operator {
  INCREMENT = '+',
  DECREMENT = '-',
  RIGHT = '>',
  LEFT = '<',
  OUTPUT = '.',
  INPUT = ',',
  FORWARD = '[',
  BACKWARD = ']',
};

struct Operation {
  Operator op;
  int count;
};

#endif
