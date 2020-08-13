#include "common.h"
#include "chunk.h"
#include "debugger.h"

int main(int argc, const char* argv[]) {
  cloxplus::Chunk chunk{};
  chunk.Write(cloxplus::OpCode::OP_RETURN);
  cloxplus::Debugger::DisassembleChunk(chunk, "Test");
  return 0;
}
