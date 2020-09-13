#include "chunk.h"
#include "debugger.h"
#include "vm.h"

#include <fmt/core.h>

#include <iostream>

int main(int argc, const char* argv[]) {
  cloxplus::Chunk chunk{};
  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 1);
  chunk.writeInstruction(chunk.writeConstant(3.14), 1);
  chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 2);

  cloxplus::VM vm{};
  cloxplus::InterpretResult result =
      vm.interpret(std::make_unique<cloxplus::Chunk>(chunk));

  std::cout << fmt::format("Result: {}", result) << std::endl;

  return 0;
}
