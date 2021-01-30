#include "compiler.h"
#include "scanner.h"
#include "token.h"
#include <fmt/core.h>
#include <iostream>

namespace cloxplus {
void Compiler::compile(const std::string& source) {
  Scanner scanner(source);
  int line = -1;
  for (;;) {
    Token token = scanner.scanToken();
    if (token.line() != line) {
      std::cout << fmt::format("{:4d} ", token.line());
      line = token.line();
    } else {
      std::cout << "   | ";
    }
    std::cout << fmt::format("{:2d} {:{}}", token.length(),
                             token.lexeme(), token.length());

    if (token.type() == TokenType::TOKEN_EOF) {
      break;
    }
  }
}
}
