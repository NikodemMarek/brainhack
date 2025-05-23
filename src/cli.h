#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <optional>
#include <vector>

enum Mode { COMPILE, ASSEMBLY, INTERPRET, DEBUG };

struct Options {
  std::string input_filename;
  std::string output_filename;
  Mode mode;
};

std::optional<Options> parse_cli(std::vector<std::string>);

#endif
