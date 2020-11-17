#include "repl.h"
#include "compiler.h"
#include "common.h"

#include <iostream>
#include <fstream>
#include <ostream>

namespace cloxplus {
void Repl::run() {
  for (;;) {
    std::cout << "> ";

    std::string line;
    if (!std::getline(std::cin, line)) {
      std::cout << std::endl;
      break;
    }

    interpret(line);
  }
}

void Repl::runFile(std::string_view path) {
  auto readFile = [](std::string_view path) {
    constexpr auto readSize = std::size_t{4096};

    auto stream = std::ifstream{path.data()};
    if (!stream) {
      std::cerr << "Could not open file '" << path << "'." << std::endl;
      exit(EXIT_FILE_ERROR);
    }
    stream.exceptions(std::ios_base::badbit);

    auto out = std::string{};
    auto buf = std::string(readSize, '\0');
    while (stream.read(&buf[0], readSize)) {
      out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
  };

  std::string source = readFile(path);
  InterpretResult result = interpret(source);

  // Next two lines are intended to reduce memory used by large source files.
  // However, shrink_to_fit() is non-binding, so may be ignored. Therefore,
  // this generally could be pointless.
  source.clear();
  source.shrink_to_fit();

  if (result == InterpretResult::INTERPRET_COMPILE_ERROR) {
    exit(EXIT_COMPILE_ERROR);
  }
  if (result == InterpretResult::INTERPRET_RUNTIME_ERROR) {
    exit(EXIT_RUNTIME_ERROR);
  }
}

InterpretResult Repl::interpret(const std::string& source) {
  Compiler::compile(source);
  return InterpretResult::INTERPRET_OK;
}
}
