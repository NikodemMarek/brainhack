#include "compiler.h"
#include "interpreter.h"
#include "parser.h"
#include "stdio.h"
#include <cstdio>
#include <functional>
#include <iostream>
#include <optional>
#include <ostream>

void print_usage(const char *program_name) {
  std::cerr << "Usage: " << program_name << " [options] <file.bf>\n"
            << "Options:\n"
            << "  -o, --output <file>   Specify output file\n"
            << "  -c, --compile         Compile to assembly\n"
            << "  -h, --help            Show this help message\n";
}

int main(int argc, char *argv[]) {
  std::optional<std::string> input_filename = std::nullopt;
  std::string output_filename = "out.asm";
  bool compile = false;

  for (int i = 1; i < argc; i++) {
    if (argv[i] == std::string("--output") || argv[i] == std::string("-o")) {
      if (i + 1 < argc) {
        output_filename = argv[i + 1];
        i++;
      } else {
        std::cerr << "Error: No output filename provided after -o flag."
                  << std::endl;
        return 1;
      }
      continue;
    }

    if (argv[i] == std::string("--compile") || argv[i] == std::string("-c")) {
      compile = true;
      continue;
    }

    if (argv[i] == std::string("--help") || argv[i] == std::string("-h")) {
      print_usage(argv[0]);
      return 0;
    }

    input_filename = argv[i];
  }

  if (!input_filename.has_value()) {
    print_usage(argv[0]);
    return 1;
  }

  auto parsed = parse_file(input_filename.value(), parse_operation);
  Tape tape(parsed);

  if (compile) {
    Compiler compiler(std::move(tape));

    std::string assembled = "";
    assembled.append(".bss\n");
    assembled.append(".lcomm bf_tape, 30000\n");
    assembled.append(".text\n");
    assembled.append(".globl _start\n");
    assembled.append("_start:\n");
    assembled.append("mov $bf_tape, %rbx\n");

    std::optional<std::string> line = compiler.next();
    while (line.has_value()) {
      assembled.append(line.value());
      line = compiler.next();
    }

    assembled.append("mov $60, %rax\n");
    assembled.append("xor %rdi, %rdi\n");
    assembled.append("syscall\n");

    FILE *file = fopen(output_filename.c_str(), "w");
    if (file == nullptr) {
      std::cerr << "Error: Could not open file " << output_filename
                << " for writing." << std::endl;
      return 1;
    }
    fprintf(file, "%s", assembled.c_str());
    fclose(file);
  } else {
    Memory memory;
    StdIO io;
    Interpreter interpreter(std::move(tape), memory, io);

    while (interpreter.next()) {
    }
  }
  return 0;
}
