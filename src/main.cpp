#include "chunk.h"
#include "vm.h"
#include "repl.h"

#include <iostream>

int main(int argc, const char* argv[]) {
  cloxplus::VM vm{};

  if (argc == 1) {
    cloxplus::Repl::run();
  } else if (argc == 2) {
    cloxplus::Repl::runFile(argv[1]);
  } else {
    std::cerr << "Usage: clox [path]" << std::endl;
    exit(EXIT_FAILURE);
  }

  return 0;
}
