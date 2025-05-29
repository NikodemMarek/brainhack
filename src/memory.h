#ifndef MEMORY_H
#define MEMORY_H

#include <optional>
#include <vector>

class Memory {
public:
  Memory();

  int get() const;
  void set(const int value);
  void change(const int by);

  void move(const int by);

protected:
  int position;
  std::vector<int> memory;

  bool is_in_bounds(const int position) const;
  void expand(const int before, const int after);
};

#endif
