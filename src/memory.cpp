#include "memory.h"
#include <stdexcept>

Memory::Memory() : memory(30000, 0), position(0) {}

bool Memory::is_in_bounds(int position) {
  return position >= 0 || position < memory.size();
}

int Memory::get() {
  if (!is_in_bounds(position))
    throw std::out_of_range("Memory position out of bounds");
  return memory[position];
}
void Memory::set(int value) {
  if (!is_in_bounds(position))
    throw std::out_of_range("Memory position out of bounds");
  memory[position] = value;
}
void Memory::change(int by) {
  if (!is_in_bounds(position))
    throw std::out_of_range("Memory position out of bounds");
  memory[position] += by;
}

void Memory::move(int by) {
  position += by;

  if (position < 0) {
    position = memory.size() + position;
  } else if (position >= memory.size()) {
    position = position - memory.size();
  }
}
