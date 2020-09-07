#include "chunk.h"
#include "debugger.h"

#include <iostream>

int main(int argc, const char* argv[]) {
  cloxplus::Chunk chunk{};
  chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 1);
  std::cout << cloxplus::Debugger::disassembleChunk(chunk, "Test") << std::endl;
  return 0;
}
