#include "utils.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Tape should find the correct bracket pairs") {
  Tape tape1 = test_tape("[]");
  REQUIRE(tape1.get_pair(0) == 1);
  REQUIRE(tape1.get_pair(1) == 0);

  Tape tape2 = test_tape("[+-><.,]");
  REQUIRE(tape2.get_pair(0) == 3);
  REQUIRE(tape2.get_pair(3) == 0);

  Tape tape3 = test_tape("[+-[><].,]");
  REQUIRE(tape3.get_pair(0) == 5);
  REQUIRE(tape3.get_pair(5) == 0);
  REQUIRE(tape3.get_pair(1) == 2);
  REQUIRE(tape3.get_pair(2) == 1);

  Tape tape4 = test_tape("[[[[[[]]]]]]");
  REQUIRE(tape4.get_pair(0) == 11);
  REQUIRE(tape4.get_pair(11) == 0);
  REQUIRE(tape4.get_pair(1) == 10);
  REQUIRE(tape4.get_pair(10) == 1);
  REQUIRE(tape4.get_pair(2) == 9);
  REQUIRE(tape4.get_pair(9) == 2);
  REQUIRE(tape4.get_pair(3) == 8);
  REQUIRE(tape4.get_pair(8) == 3);
  REQUIRE(tape4.get_pair(4) == 7);
  REQUIRE(tape4.get_pair(7) == 4);
  REQUIRE(tape4.get_pair(5) == 6);
  REQUIRE(tape4.get_pair(6) == 5);

  Tape tape5 = test_tape("[+-[><[]].,[+]]");
  REQUIRE(tape5.get_pair(0) == 10);
  REQUIRE(tape5.get_pair(10) == 0);
  REQUIRE(tape5.get_pair(1) == 4);
  REQUIRE(tape5.get_pair(4) == 1);
  REQUIRE(tape5.get_pair(2) == 3);
  REQUIRE(tape5.get_pair(3) == 2);
  REQUIRE(tape5.get_pair(7) == 9);
  REQUIRE(tape5.get_pair(9) == 7);

  Tape tape6 = test_tape(">+[<+>]-");
  REQUIRE(tape6.get_pair(2) == 6);
  REQUIRE(tape6.get_pair(6) == 2);
}
