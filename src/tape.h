#ifndef TAPE_H
#define TAPE_H

#include "operation.h"
#include <map>
#include <optional>
#include <vector>

class Tape {
public:
  Tape(std::vector<Operation> input);

  std::optional<Operation> at(int position);
  std::optional<Operation> next();

  std::optional<int> get_pair(int start);

  void branch(int to);

  int get_position();

private:
  int position;
  std::vector<Operation> input;
  std::map<int, int> brackets;
};

#endif
