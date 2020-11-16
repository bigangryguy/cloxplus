#include "chunk.h"
#include "vm.h"

#include <fmt/core.h>

#include <iostream>

int main(int argc, const char* argv[]) {
  cloxplus::Chunk chunk{};
  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 1);
  chunk.writeInstruction(chunk.writeConstant(3.15), 1);
  chunk.writeInstruction(cloxplus::OpCode::OP_NEGATE, 1);
  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 1);
  chunk.writeInstruction(chunk.writeConstant(10), 1);
  chunk.writeInstruction(cloxplus::OpCode::OP_ADD, 1);
  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 1);
  chunk.writeInstruction(chunk.writeConstant(2), 1);
  chunk.writeInstruction(cloxplus::OpCode::OP_SUBTRACT, 1);
  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 1);
  chunk.writeInstruction(chunk.writeConstant(4), 1);
  chunk.writeInstruction(cloxplus::OpCode::OP_MULTIPLY, 1);
  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 1);
  chunk.writeInstruction(chunk.writeConstant(5), 1);
  chunk.writeInstruction(cloxplus::OpCode::OP_DIVIDE, 1);
  chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 1);

  cloxplus::VM vm{};
  cloxplus::InterpretResult result =
      vm.interpret(std::make_unique<cloxplus::Chunk>(chunk));

  std::cout << fmt::format("Result: {}", result) << std::endl;

  return 0;
}
