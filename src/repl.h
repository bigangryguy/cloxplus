#pragma once

#include "interpretresult.h"

#include <string>

namespace cloxplus {
class Repl {
public:
  static void run();
  static void runFile(std::string_view path);
private:
  static InterpretResult interpret(const std::string& source);
};
}
