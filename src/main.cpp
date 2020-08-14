#include "chunk.h"
#include "debugger.h"

#include <iostream>

int main(int argc, const char* argv[]) {
  cloxplus::Chunk chunk{};
  chunk.write(cloxplus::OpCode::OP_RETURN);
  std::cout << cloxplus::Debugger::disassembleChunk(chunk, "Test") << std::endl;
  return 0;
}
