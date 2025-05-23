#include "utils.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("interpreter should change memory") {
  auto tape = test_tape("+++++.-----.");
  auto memory = test_memory();
  auto io = test_io();
  auto operations = test_interpreter(tape, memory, io);
  while (operations.next()) {
  }
  REQUIRE(io.is_at_val(0, 5));
  REQUIRE(io.is_at_val(1, 0));
}

TEST_CASE("interpreter should move memory pointer") {
  auto tape = test_tape("+++++>>>>>.<<<<<.");
  auto memory = test_memory();
  auto io = test_io();
  auto operations = test_interpreter(tape, memory, io);
  while (operations.next()) {
  }
  REQUIRE(io.is_at_val(0, 0));
  REQUIRE(io.is_at_val(1, 5));
}

TEST_CASE("interpreter should input and output values") {
  auto input = "8hP (+\n";
  auto tape = test_tape(",.,.,.,.,.,.,.");
  auto memory = test_memory();
  auto io = test_io(input);
  auto operations = test_interpreter(tape, memory, io);
  while (operations.next()) {
  }
  REQUIRE(io.input_buffer == "");
  REQUIRE(io.output_buffer == input);
}

TEST_CASE("interpreter should branch forward when value is 0") {
  auto tape = test_tape("[.>]++.");
  auto memory = test_memory();
  auto io = test_io();
  auto operations = test_interpreter(tape, memory, io);
  while (operations.next()) {
  }
  REQUIRE(io.is_at_val(0, 2));
}

TEST_CASE("interpreter should not branch forward when value is not 0") {
  auto tape = test_tape("+.[>.]++.");
  auto memory = test_memory();
  auto io = test_io();
  auto operations = test_interpreter(tape, memory, io);
  while (operations.next()) {
  }
  REQUIRE(io.is_at_val(0, 1));
  REQUIRE(io.is_at_val(1, 0));
  REQUIRE(io.is_at_val(2, 2));
}

TEST_CASE("interpreter should branch backwards") {
  auto tape = test_tape("+++++[.-]");
  auto memory = test_memory();
  auto io = test_io();
  auto operations = test_interpreter(tape, memory, io);
  while (operations.next()) {
  }
  REQUIRE(io.is_at_val(0, 5));
  REQUIRE(io.is_at_val(1, 4));
  REQUIRE(io.is_at_val(2, 3));
  REQUIRE(io.is_at_val(3, 2));
  REQUIRE(io.is_at_val(4, 1));
  REQUIRE(io.is_at_val(5, 0));
}

TEST_CASE("interpreter should output 'Hello world!'") {
  std::string hello_world = ">+++++++++[<++++++++>-]<.>+++++++[<++++>-]<+.+++++"
                            "++..+++.[-]>++++++++[<++++>-]"
                            "<.>+++++++++++[<++++++++>-]<-.--------.+++.------."
                            "--------.[-]>++++++++[<++++>-]<+.[-]++++++++++.";
  auto tape = test_tape(hello_world);
  auto memory = test_memory();
  auto io = test_io();
  auto operations = test_interpreter(tape, memory, io);
  while (operations.next()) {
  }
  REQUIRE(io.output_buffer == "Hello world!\n");
}
