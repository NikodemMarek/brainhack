#include "utils.h"
#include <catch2/catch_test_macros.hpp>

std::tuple<std::optional<Operation>, std::optional<Operation>>
combine(Operation a, Operation b);

TEST_CASE("combine should combine change operations correctly") {
  Operation a1{Operator::INCREMENT, 2};
  Operation b1{Operator::INCREMENT, 3};
  std::optional<Operation> combined1;
  std::optional<Operation> new_op1;
  std::tie(combined1, new_op1) = combine(a1, b1);
  REQUIRE(combined1 == Operation{Operator::INCREMENT, 5});
  REQUIRE(new_op1 == std::nullopt);

  Operation a2{Operator::INCREMENT, 2};
  Operation b2{Operator::DECREMENT, 1};
  std::optional<Operation> combined2;
  std::optional<Operation> new_op2;
  std::tie(combined2, new_op2) = combine(a2, b2);
  REQUIRE(combined2 == Operation{Operator::INCREMENT, 1});
  REQUIRE(new_op2 == std::nullopt);

  Operation a3{Operator::DECREMENT, 3};
  Operation b3{Operator::INCREMENT, 2};
  std::optional<Operation> combined3;
  std::optional<Operation> new_op3;
  std::tie(combined3, new_op3) = combine(a3, b3);
  REQUIRE(combined3 == Operation{Operator::DECREMENT, 1});
  REQUIRE(new_op3 == std::nullopt);

  Operation a4{Operator::DECREMENT, 2};
  Operation b4{Operator::DECREMENT, 3};
  std::optional<Operation> combined4;
  std::optional<Operation> new_op4;
  std::tie(combined4, new_op4) = combine(a4, b4);
  REQUIRE(combined4 == Operation{Operator::DECREMENT, 5});
  REQUIRE(new_op4 == std::nullopt);

  Operation a5{Operator::INCREMENT, 2};
  Operation b5{Operator::DECREMENT, 2};
  std::optional<Operation> combined5;
  std::optional<Operation> new_op5;
  std::tie(combined5, new_op5) = combine(a5, b5);
  REQUIRE(combined5 == std::nullopt);
  REQUIRE(new_op5 == std::nullopt);
}

TEST_CASE("combine should combine move operations correctly") {
  Operation a1{Operator::RIGHT, 2};
  Operation b1{Operator::RIGHT, 3};
  std::optional<Operation> combined1;
  std::optional<Operation> new_op1;
  std::tie(combined1, new_op1) = combine(a1, b1);
  REQUIRE(combined1 == Operation{Operator::RIGHT, 5});
  REQUIRE(new_op1 == std::nullopt);

  Operation a2{Operator::RIGHT, 2};
  Operation b2{Operator::LEFT, 1};
  std::optional<Operation> combined2;
  std::optional<Operation> new_op2;
  std::tie(combined2, new_op2) = combine(a2, b2);
  REQUIRE(combined2 == Operation{Operator::RIGHT, 1});
  REQUIRE(new_op2 == std::nullopt);

  Operation a3{Operator::LEFT, 3};
  Operation b3{Operator::RIGHT, 2};
  std::optional<Operation> combined3;
  std::optional<Operation> new_op3;
  std::tie(combined3, new_op3) = combine(a3, b3);
  REQUIRE(combined3 == Operation{Operator::LEFT, 1});
  REQUIRE(new_op3 == std::nullopt);

  Operation a4{Operator::LEFT, 2};
  Operation b4{Operator::LEFT, 3};
  std::optional<Operation> combined4;
  std::optional<Operation> new_op4;
  std::tie(combined4, new_op4) = combine(a4, b4);
  REQUIRE(combined4 == Operation{Operator::LEFT, 5});
  REQUIRE(new_op4 == std::nullopt);

  Operation a5{Operator::RIGHT, 2};
  Operation b5{Operator::LEFT, 2};
  std::optional<Operation> combined5;
  std::optional<Operation> new_op5;
  std::tie(combined5, new_op5) = combine(a5, b5);
  REQUIRE(combined5 == std::nullopt);
  REQUIRE(new_op5 == std::nullopt);
}

TEST_CASE("combine should combine io operations correctly") {
  Operation a1{Operator::INPUT, 2};
  Operation b1{Operator::INPUT, 3};
  std::optional<Operation> combined1;
  std::optional<Operation> new_op1;
  std::tie(combined1, new_op1) = combine(a1, b1);
  REQUIRE(combined1 == Operation{Operator::INPUT, 5});
  REQUIRE(new_op1 == std::nullopt);

  Operation a2{Operator::INPUT, 2};
  Operation b2{Operator::OUTPUT, 1};
  std::optional<Operation> combined2;
  std::optional<Operation> new_op2;
  std::tie(combined2, new_op2) = combine(a2, b2);
  REQUIRE(combined2 == Operation{Operator::INPUT, 2});
  REQUIRE(new_op2 == Operation{Operator::OUTPUT, 1});

  Operation a3{Operator::OUTPUT, 3};
  Operation b3{Operator::INPUT, 2};
  std::optional<Operation> combined3;
  std::optional<Operation> new_op3;
  std::tie(combined3, new_op3) = combine(a3, b3);
  REQUIRE(combined3 == Operation{Operator::OUTPUT, 3});
  REQUIRE(new_op3 == Operation{Operator::INPUT, 2});

  Operation a4{Operator::OUTPUT, 2};
  Operation b4{Operator::OUTPUT, 3};
  std::optional<Operation> combined4;
  std::optional<Operation> new_op4;
  std::tie(combined4, new_op4) = combine(a4, b4);
  REQUIRE(combined4 == Operation{Operator::OUTPUT, 5});
  REQUIRE(new_op4 == std::nullopt);

  Operation a5{Operator::OUTPUT, 2};
  Operation b5{Operator::INPUT, 2};
  std::optional<Operation> combined5;
  std::optional<Operation> new_op5;
  std::tie(combined5, new_op5) = combine(a5, b5);
  REQUIRE(combined5 == Operation{Operator::OUTPUT, 2});
  REQUIRE(new_op5 == Operation{Operator::INPUT, 2});
}

TEST_CASE("combine should combine branch operations correctly") {
  Operation a1{Operator::FORWARD, 1};
  Operation b1{Operator::FORWARD, 1};
  std::optional<Operation> combined1;
  std::optional<Operation> new_op1;
  std::tie(combined1, new_op1) = combine(a1, b1);
  REQUIRE(combined1 == Operation{Operator::FORWARD, 1});
  REQUIRE(new_op1 == Operation{Operator::FORWARD, 1});

  Operation a2{Operator::FORWARD, 1};
  Operation b2{Operator::BACKWARD, 1};
  std::optional<Operation> combined2;
  std::optional<Operation> new_op2;
  std::tie(combined2, new_op2) = combine(a2, b2);
  REQUIRE(combined2 == Operation{Operator::FORWARD, 1});
  REQUIRE(new_op2 == Operation{Operator::BACKWARD, 1});

  Operation a3{Operator::BACKWARD, 1};
  Operation b3{Operator::FORWARD, 1};
  std::optional<Operation> combined3;
  std::optional<Operation> new_op3;
  std::tie(combined3, new_op3) = combine(a3, b3);
  REQUIRE(combined3 == Operation{Operator::BACKWARD, 1});
  REQUIRE(new_op3 == Operation{Operator::FORWARD, 1});

  Operation a4{Operator::BACKWARD, 1};
  Operation b4{Operator::BACKWARD, 1};
  std::optional<Operation> combined4;
  std::optional<Operation> new_op4;
  std::tie(combined4, new_op4) = combine(a4, b4);
  REQUIRE(combined4 == Operation{Operator::BACKWARD, 1});
  REQUIRE(new_op4 == Operation{Operator::BACKWARD, 1});
}

TEST_CASE("parser should return the correct operations") {
  auto operations = test_parse("+>-<.,[]");
  REQUIRE(operations.size() == 8);
  REQUIRE(operations[0] == Operation{Operator::INCREMENT, 1});
  REQUIRE(operations[1] == Operation{Operator::RIGHT, 1});
  REQUIRE(operations[2] == Operation{Operator::DECREMENT, 1});
  REQUIRE(operations[3] == Operation{Operator::LEFT, 1});
  REQUIRE(operations[4] == Operation{Operator::OUTPUT, 1});
  REQUIRE(operations[5] == Operation{Operator::INPUT, 1});
  REQUIRE(operations[6] == Operation{Operator::FORWARD, 1});
  REQUIRE(operations[7] == Operation{Operator::BACKWARD, 1});
}

TEST_CASE("parser should return the correct number of operations") {
  auto operations1 = test_parse("++>>>--<<..,,");
  REQUIRE(operations1[0] == Operation{Operator::INCREMENT, 2});
  REQUIRE(operations1[1] == Operation{Operator::RIGHT, 3});
  REQUIRE(operations1[2] == Operation{Operator::DECREMENT, 2});
  REQUIRE(operations1[3] == Operation{Operator::LEFT, 2});
  REQUIRE(operations1[4] == Operation{Operator::OUTPUT, 2});

  auto operations2 = test_parse("[[]]");
  REQUIRE(operations2[0] == Operation{Operator::FORWARD, 1});
  REQUIRE(operations2[1] == Operation{Operator::FORWARD, 1});
  REQUIRE(operations2[2] == Operation{Operator::BACKWARD, 1});
  REQUIRE(operations2[3] == Operation{Operator::BACKWARD, 1});
}
