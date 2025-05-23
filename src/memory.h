#ifndef MEMORY_H
#define MEMORY_H

#include <optional>
#include <vector>

class Memory {
public:
  Memory();

  int get();
  void set(int value);
  void change(int by);

  void move(int by);

protected:
  int position;
  std::vector<int> memory;

  bool is_in_bounds(int position);
};

#endif
