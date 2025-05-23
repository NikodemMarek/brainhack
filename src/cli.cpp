#include "cli.h"

void print_usage(const std::string program_name) {
  std::cerr << "Usage: " << program_name << " [options] <file.bf>\n"
            << "Options:\n"
            << "  -o, --output <file>   Specify output file\n"
            << "  -c, --compile         Compile to binary\n"
            << "  -a, --assembly        Generate assembly\n"
            << "  -d, --debug           Debug mode\n"
            << "  -h, --help            Show this help message\n";
}

std::optional<Options> parse_cli(std::vector<std::string> args) {
  std::optional<std::string> input_filename = std::nullopt;
  std::optional<std::string> output_filename = std::nullopt;
  Mode mode = Mode::INTERPRET;

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
      if (mode == Mode::ASSEMBLY) {
        std::cerr << "Error: Cannot use --compile and --assembly together."
                  << std::endl;
        return std::nullopt;
      }
      if (mode == Mode::DEBUG) {
        std::cerr << "Error: Cannot use --compile and --debug together."
                  << std::endl;
        return std::nullopt;
      }

      mode = Mode::COMPILE;
      continue;
    }

    if (args[i] == std::string("--assembly") || args[i] == std::string("-a")) {
      if (mode == Mode::COMPILE) {
        std::cerr << "Error: Cannot use --assembly and --compile together."
                  << std::endl;
        return std::nullopt;
      }
      if (mode == Mode::DEBUG) {
        std::cerr << "Error: Cannot use --assembly and --debug together."
                  << std::endl;
        return std::nullopt;
      }

      mode = Mode::ASSEMBLY;
      continue;
    }

    if (args[i] == std::string("--debug") || args[i] == std::string("-d")) {
      if (mode == Mode::COMPILE) {
        std::cerr << "Error: Cannot use --debug and --compile together."
                  << std::endl;
        return std::nullopt;
      }
      if (mode == Mode::ASSEMBLY) {
        std::cerr << "Error: Cannot use --debug and --assembly together."
                  << std::endl;
        return std::nullopt;
      }

      mode = Mode::DEBUG;
      continue;
    }

    if (args[i] == std::string("--help") || args[i] == std::string("-h")) {
      print_usage(args[0]);
      return std::nullopt;
    }

    input_filename = args[i];
  }

  if (!output_filename.has_value()) {
    if (mode == Mode::ASSEMBLY) {
      output_filename = "out.asm";
    } else {
      output_filename = "out";
    }
  }

  if (!input_filename.has_value()) {
    print_usage(args[0]);
    return std::nullopt;
  }

  return Options{input_filename.value(), output_filename.value(), mode};
}
