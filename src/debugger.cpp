#include "debugger.h"
#include <cctype>
#include <format>
#include <iostream>
#include <ostream>
#include <string>

DebuggerMemory::DebuggerMemory() : Memory() {}

std::vector<int> DebuggerMemory::get_range(int start, int end) {
  std::vector<int> range;
  for (int i = start; i < end; ++i) {
    range.push_back(memory[i]);
  }
  return range;
}

std::string ascii_to_human_readable(int value) {
  switch (value) {
  case 0:
    return "NUL";
  case 1:
    return "SOH";
  case 2:
    return "STX";
  case 3:
    return "ETX";
  case 4:
    return "EOT";
  case 5:
    return "ENQ";
  case 6:
    return "ACK";
  case 7:
    return "BEL";
  case 8:
    return "BS";
  case 9:
    return "TAB";
  case 10:
    return "LF";
  case 11:
    return "VT";
  case 12:
    return "FF";
  case 13:
    return "CR";
  case 14:
    return "SO";
  case 15:
    return "SI";
  case 16:
    return "DLE";
  case 17:
    return "DC1";
  case 18:
    return "DC2";
  case 19:
    return "DC3";
  case 20:
    return "DC4";
  case 21:
    return "NAK";
  case 22:
    return "SYN";
  case 23:
    return "ETB";
  case 24:
    return "CAN";
  case 25:
    return "EM";
  case 26:
    return "SUB";
  case 27:
    return "ESC";
  case 28:
    return "FS";
  case 29:
    return "GS";
  case 30:
    return "RS";
  case 31:
    return "US";
  }
  return std::string(1, static_cast<char>(value));
}

std::string DebuggerMemory::print_range() {
  int start = position - 5 < 0 ? 0 : position - 5;
  int end = position + 5 > memory.size() ? memory.size() : position + 5;
  auto start_str = std::to_string(start);
  std::string frame_line = std::string(start_str.size(), ' ') + " +";
  std::string values_line = start_str + " |";
  std::string pointer_line = std::string(start_str.size(), ' ') + "  ";

  int index = start;
  for (auto value : get_range(start, end)) {
    auto formatted_value =
        std::format("{} ({})", value, ascii_to_human_readable(value));
    frame_line += std::string(formatted_value.size() + 2, '-') + "+";
    values_line += std::format(" {} |", formatted_value);

    if (index == position) {
      if (formatted_value.size() % 2 == 0) {
        auto padding = std::string(formatted_value.size() / 2, ' ');
        pointer_line += padding + "^ " + padding;
      } else {
        auto padding = std::string(formatted_value.size() / 2, ' ');
        pointer_line += padding + " ^ " + padding;
      }
    } else {
      pointer_line += std::string(formatted_value.size() + 3, ' ');
    }
    index++;
  }
  return frame_line + "\n" + values_line + " " + std::to_string(end) + "\n" +
         frame_line + "\n" + pointer_line;
}

int DebuggerMemory::pointer() { return position; }

DebugIO::DebugIO() : output_buffer() {}

void DebugIO::output(char c, int count) {
  for (int i = 0; i < count; i++) {
    output_buffer += c;
  }
}
char DebugIO::input(int count) {
  char c;
  for (int i = 0; i < count; i++) {
    c = getchar();
  }
  return c;
}

std::string DebugIO::get_output() { return output_buffer; }

Debugger::Debugger(Tape &tape)
    : tape(tape), memory(), io(), interpreter(tape, memory, io) {}

std::string print_operation(const Operation &operation,
                            const int current_memory_value,
                            const int current_pointer_value) {
  switch (operation.op) {
  case Operator::INCREMENT:
    return std::format("INCREMENT VALUE BY {} ({} + {} = {})", operation.count,
                       current_memory_value,
                       current_memory_value + operation.count,
                       current_memory_value + operation.count);
  case Operator::DECREMENT:
    return std::format("DECREMENT VALUE BY {} ({} - {} = {})", operation.count,
                       current_memory_value,
                       current_memory_value - operation.count,
                       current_memory_value - operation.count);
  case Operator::RIGHT:
    return std::format("INCREMENT POINTER BY {} ({} > {} = {})",
                       operation.count, current_pointer_value, operation.count,
                       current_pointer_value + operation.count);
  case Operator::LEFT:
    return std::format("DECREMENT POINTER BY {} ({} < {} = {})",
                       operation.count, current_pointer_value, operation.count,
                       current_pointer_value - operation.count);
  case Operator::OUTPUT:
    if (operation.count == 1) {
      return std::format("PRINT CHARACTER {} ('{}')",
                         static_cast<char>(current_memory_value),
                         current_memory_value);
    } else {
      return std::format("PRINT CHARACTER {} ('{}') {} TIMES",
                         static_cast<char>(current_memory_value),
                         current_memory_value, operation.count);
    }
  case Operator::INPUT:
    if (operation.count == 1) {
      return std::format("GET CHARACTER");
    } else {
      return std::format("GET {} CHARACTERS", operation.count);
    }
  case Operator::FORWARD:
    if (current_memory_value == 0) {
      return std::format("JUMP FORWARD ({} == 0)", current_memory_value);
    } else {
      return std::format("SKIP JUMP ({} != 0)", current_memory_value);
    }
  case Operator::BACKWARD:
    if (current_memory_value != 0) {
      return std::format("JUMP BACKWARD ({} != 0)", current_memory_value);
    } else {
      return std::format("SKIP JUMP ({} == 0)", current_memory_value);
    }
  }
  return "NONE";
}

std::string Debugger::print_state() {
  return "Output: " + io.get_output() + "\n\n" + memory.print_range() +
         "\nNext operation: " +
         print_operation(*tape.peek(), memory.get(), +memory.pointer()) +
         "\n\n" + "[number]Enter - execute next operation(s) | q - quit";
}

bool Debugger::next() {
  while (true) {
    std::cout << "\033[2J\033[1;1H" << print_state() << std::endl;

    std::string input;
    std::getline(std::cin, input);
    if (input == "q") {
      return false;
    } else if (input == "") {
      return interpreter.next();
    } else {
      try {
        int count = std::stoi(input);
        for (int i = 0; i < count; ++i) {
          if (!interpreter.next()) {
            std::cout << "\033[2J\033[1;1H" << print_state() << std::endl;
            return false;
          }
        }
      } catch (void *e) {
        // Just ignore the exception
      }
    }
  }

  return false;
}
