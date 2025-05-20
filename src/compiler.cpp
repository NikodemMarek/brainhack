#include "compiler.h"
#include <optional>

Compiler::Compiler(Tape &&tape) : tape(tape) {}

std::optional<std::string> Compiler::next() {
  std::optional<Operation> operation = tape.next();
  if (!operation.has_value()) {
    return std::nullopt;
  }

  int count = operation.value().count;
  switch (operation.value().op) {
  case Operator::INCREMENT:
    return "addq $" + std::to_string(count) + ", (%rbx)\n";
    break;
  case Operator::DECREMENT:
    return "subq $" + std::to_string(count) + ", (%rbx)\n";
    break;

  case Operator::RIGHT:
    return "addq $" + std::to_string(count) + ", %rbx\n";
    break;
  case Operator::LEFT:
    return "subq $" + std::to_string(count) + ", %rbx\n";
    break;

  case Operator::OUTPUT:
    return "mov $1, %rax\nmov $1, %rdi\nmov %rbx, %rsi\nmov $1, "
           "%rdx\nsyscall\n";
    break;
  case Operator::INPUT:
    return "mov $1, %rax\nmov $0, %rdi\nmov %rbx, %rsi\nmov $1, "
           "%rdx\nsyscall\n";
    break;

  case Operator::FORWARD: {
    int pair_id = tape.get_pair(tape.get_position() - 1).value();
    return "cmpb $0, (%rbx)\nje .B" + std::to_string(pair_id) + "\n.F" +
           std::to_string(pair_id) + ":\n";
  } break;
  case Operator::BACKWARD: {
    int pair_id = tape.get_position() - 1;
    return "cmpb $0, (%rbx)\njne .F" + std::to_string(pair_id) + "\n.B" +
           std::to_string(pair_id) + ":\n";
  } break;
  }

  return std::nullopt;
}
