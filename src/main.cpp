#include "cli.h"
#include "compiler.h"
#include "debugger.h"
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

  if (options.mode == Mode::COMPILE || options.mode == Mode::ASSEMBLY) {
    Compiler compiler(std::move(tape), GnuAssembly());
    std::string assembled = compiler.complie();

    std::string assembly_output_filename = "/tmp/brainhack_out.asm";
    if (options.mode == Mode::ASSEMBLY) {
      assembly_output_filename = options.output_filename;
    }

    FILE *file = fopen(assembly_output_filename.c_str(), "w");
    if (file == nullptr) {
      if (options.mode == Mode::ASSEMBLY) {
        std::cerr << "Error: Could not open file " << options.output_filename
                  << " for writing." << std::endl;
      } else {
        std::cerr << "Error: Could not generate assembly file." << std::endl;
      }
      return 1;
    }
    fprintf(file, "%s", assembled.c_str());
    fclose(file);

    if (options.mode == Mode::ASSEMBLY) {
      std::cout << "Assembly file generated: `" << options.output_filename
                << "`" << std::endl;
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
    std::cout << "Compiled successfully to `" << options.output_filename << "`"
              << std::endl;
  } else if (options.mode == Mode::INTERPRET) {
    Memory memory;
    StdIO io;
    Interpreter interpreter(tape, memory, io);

    while (interpreter.next()) {
    }
  } else if (options.mode == Mode::DEBUG) {
    Debugger debugger(tape);
    std::cout << "Debugging mode activated." << std::endl;
    while (debugger.next()) {
    }
    std::cout << "Exiting debug mode." << std::endl;
  }
  return 0;
}
