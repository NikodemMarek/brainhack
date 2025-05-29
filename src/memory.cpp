#include "memory.h"

Memory::Memory() : memory(30000, 0), position(0) {}

void Memory::expand(const int before, const int after) {
  if (before < 0 || after < 0)
    return;

  if (before > 0) {
    memory.insert(memory.begin(), before, 0);
    position += before;
  }
  if (after > 0) {
    memory.insert(memory.end(), after, 0);
  }
}
bool Memory::is_in_bounds(const int position) const {
  return position >= 0 || position < memory.size();
}

int Memory::get() const {
  if (!is_in_bounds(position))
    return 0;
  return memory[position];
}
void Memory::set(const int value) {
  if (!is_in_bounds(position))
    return;
  memory[position] = value;
}
void Memory::change(const int by) {
  if (!is_in_bounds(position))
    return;
  memory[position] += by;
}

void Memory::move(const int by) {
  position += by;

  if (position < 0) {
    expand(-position, 0);
  } else if (position >= memory.size()) {
    expand(0, position - memory.size() + 1);
  }
}
