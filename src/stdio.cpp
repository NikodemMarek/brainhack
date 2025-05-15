#include "stdio.h"
#include <cstdio>

void StdIO::output(char c, int count) {
  for (int i = 0; i < count; i++) {
    putchar(c);
  }
}
char StdIO::input(int count) {
  char c;
  for (int i = 0; i < count; i++) {
    c = getchar();
  }
  return c;
}
