#ifndef PARSER_H
#define PARSER_H

#include "operation.h"
#include <functional>
#include <optional>
#include <string>
#include <vector>

std::tuple<std::optional<Operation>, std::optional<Operation>>
combine(Operation a, Operation b);

std::vector<Operation>
parse(std::string input, std::function<std::optional<Operator>(char)> parser);
std::optional<Operator> parse_operation(char c);

std::vector<Operation>
parse_file(const std::string &path,
           std::function<std::optional<Operator>(char)> parser);

#endif
