#include "chunk.h"
#include "debugger.h"

#include <iostream>

int main(int argc, const char* argv[]) {
  cloxplus::Chunk chunk{};
  chunk.Write(cloxplus::OpCode::OP_RETURN);
  std::cout <<
      cloxplus::Debugger::DisassembleChunk(chunk, "Test") << std::endl;
  return 0;
}
