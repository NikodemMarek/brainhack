#include "cli.h"
#include "compiler.h"
#include "interpreter.h"
#include "parser.h"
#include "stdio.h"
#include <cstdio>
#include <functional>
#include <iostream>
#include <optional>
#include <ostream>

int main(int argc, char *argv[]) {
  std::vector<std::string> args(argv, argv + argc);
  std::optional<Options> roptions = parse_cli(args);
  if (!roptions.has_value()) {
    return 0;
  }
  auto options = roptions.value();

  auto parsed = parse_file(options.input_filename, parse_operation);
  Tape tape(parsed);

  if (options.compile || options.assembly) {
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

    std::string assembly_output_filename = "/tmp/brainhack_out.asm";
    if (options.assembly) {
      assembly_output_filename = options.output_filename;
    }

    FILE *file = fopen(assembly_output_filename.c_str(), "w");
    if (file == nullptr) {
      if (options.assembly) {
        std::cerr << "Error: Could not open file " << options.output_filename
                  << " for writing." << std::endl;
      } else {
        std::cerr << "Error: Could not generate assembly file." << std::endl;
      }
      return 1;
    }
    fprintf(file, "%s", assembled.c_str());
    fclose(file);

    if (options.assembly) {
      return 0;
    }

    if (system("as /tmp/brainhack_out.asm -o /tmp/brainhack_out.o") != 0) {
      std::cerr << "Error: Could not assemble the output file." << std::endl;
      return 1;
    }
    if (system(("ld /tmp/brainhack_out.o -o " + options.output_filename)
                   .c_str()) != 0) {
      std::cerr << "Error: Could not link the output file." << std::endl;
      return 1;
    }
  } else {
    Memory memory;
    StdIO io;
    Interpreter interpreter(std::move(tape), memory, io);

    while (interpreter.next()) {
    }
  }
  return 0;
}
