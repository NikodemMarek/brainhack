#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <optional>
#include <vector>

struct Options {
  std::string input_filename;
  std::string output_filename;
  bool compile = false;
  bool assembly = false;
};

std::optional<Options> parse_cli(std::vector<std::string>);

#endif
