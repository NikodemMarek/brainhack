#include "compiler.h"
#include <optional>

std::string GnuAssembly::prologue() const {
  return ".bss\n"
         ".lcomm bf_tape, 30000\n"
         ".text\n"
         ".globl _start\n"
         "_start:\n"
         "mov $bf_tape, %rbx\n";
}
std::string GnuAssembly::epilogue() const {
  return "mov $60, %rax\n"
         "xor %rdi, %rdi\n"
         "syscall\n";
}

std::string GnuAssembly::operation(const Tape &tape,
                                   const Operation &operation) const {
  int count = operation.count;
  switch (operation.op) {
  case Operator::INCREMENT:
    return "addq $" + std::to_string(count) + ", (%rbx)\n";
  case Operator::DECREMENT:
    return "subq $" + std::to_string(count) + ", (%rbx)\n";

  case Operator::RIGHT:
    return "addq $" + std::to_string(count) + ", %rbx\n";
  case Operator::LEFT:
    return "subq $" + std::to_string(count) + ", %rbx\n";

  case Operator::OUTPUT: {
    std::string res = "mov $1, %rax\nmov $1, %rdi\nmov %rbx, %rsi\nmov $1, "
                      "%rdx\n";
    for (int i = 0; i < count; i++) {
      res += "syscall\n";
    }
    return res;
  }
  case Operator::INPUT: {
    std::string res = "";
    for (int i = 1; i < count; i++) {
      res += "mov $0, %rax\nmov $0, %rdi\nmov %rbx, %rsi\nmov $1, "
             "%rdx\nsyscall\n";
    }
    return res;
  }

  case Operator::FORWARD: {
    int pair_id = tape.get_pair(tape.get_position() - 1).value();
    return "cmpb $0, (%rbx)\nje .B" + std::to_string(pair_id) + "\n.F" +
           std::to_string(pair_id) + ":\n";
  }
  case Operator::BACKWARD: {
    int pair_id = tape.get_position() - 1;
    return "cmpb $0, (%rbx)\njne .F" + std::to_string(pair_id) + "\n.B" +
           std::to_string(pair_id) + ":\n";
  }
  }

  return "";
}
