#ifndef TAPE_H
#define TAPE_H

#include "operation.h"
#include <map>
#include <optional>
#include <vector>

class Tape {
public:
  Tape(std::vector<Operation> input);

  std::optional<Operation> at(const int position) const;
  std::optional<Operation> next();
  std::optional<Operation> peek() const;

  std::optional<int> get_pair(const int start) const;

  void branch(const int to);

  int get_position() const;

private:
  int position;
  std::vector<Operation> input;
  std::map<int, int> brackets;
};

#endif
