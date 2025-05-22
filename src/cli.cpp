#include "cli.h"

void print_usage(const std::string program_name) {
  std::cerr << "Usage: " << program_name << " [options] <file.bf>\n"
            << "Options:\n"
            << "  -o, --output <file>   Specify output file\n"
            << "  -c, --compile         Compile to binary\n"
            << "  -a, --assembly        Generate assembly\n"
            << "  -h, --help            Show this help message\n";
}

std::optional<Options> parse_cli(std::vector<std::string> args) {
  std::optional<std::string> input_filename = std::nullopt;
  std::optional<std::string> output_filename = std::nullopt;
  bool compile = false;
  bool assembly = false;

  for (int i = 1; i < args.size(); i++) {
    if (args[i] == std::string("--output") || args[i] == std::string("-o")) {
      if (i + 1 < args.size()) {
        output_filename = args[i + 1];
        i++;
      } else {
        std::cerr << "Error: No output filename provided after -o flag."
                  << std::endl;
        return std::nullopt;
      }
      continue;
    }

    if (args[i] == std::string("--compile") || args[i] == std::string("-c")) {
      compile = true;
      continue;
    }

    if (args[i] == std::string("--assembly") || args[i] == std::string("-a")) {
      assembly = true;
      continue;
    }

    if (args[i] == std::string("--help") || args[i] == std::string("-h")) {
      print_usage(args[0]);
      return std::nullopt;
    }

    input_filename = args[i];
  }

  if (!output_filename.has_value()) {
    if (assembly) {
      output_filename = "out.asm";
    } else {
      output_filename = "out";
    }
  }

  if (!input_filename.has_value()) {
    print_usage(args[0]);
    return std::nullopt;
  }

  return Options{input_filename.value(), output_filename.value(), compile,
                 assembly};
}
