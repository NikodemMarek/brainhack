#include "utils.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("compiler should generate assembly for a simple program") {
  auto tape = test_tape("+>-<.,[]");
  auto compiler = test_compiler(tape);
  auto compiled = compiler.complie();
  REQUIRE(compiled ==
          "bf_tape declaration\nstart function definition\nincrement 1\nright "
          "1\ndecrement 1\nleft 1\noutput 1\ninput 1\nforward\nbackward\ncall "
          "to end the program\n");
}
