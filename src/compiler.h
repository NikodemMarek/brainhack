#ifndef COMPILER_H
#define COMPILER_H

#include "tape.h"
#include <string>

class GnuAssembly {
public:
  std::string prologue() const;
  std::string epilogue() const;
  std::string operation(const Tape &tape, const Operation &operation) const;
};

template <typename Assembly> class Compiler {
public:
  Compiler(Tape &&tape, Assembly &&assembly)
      : assembly(std::forward<Assembly>(assembly)), tape(std::move(tape)) {}

  std::string complie() {
    std::string assembled = "";
    std::optional<Operation> op = tape.next();
    while (op.has_value()) {
      assembled.append(assembly.operation(tape, op.value()));
      op = tape.next();
    }

    return assembly.prologue() + assembled + assembly.epilogue();
  }

private:
  Assembly assembly;
  Tape tape;
};

#endif
