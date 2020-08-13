#include "debugger.h"

#include <iostream>

namespace cloxplus {
void Debugger::DisassembleChunk(const Chunk& chunk, const std::string& name)
{
  std::cout << "== " << name << " ==" << std::endl;

  for (auto offset = 0; offset < chunk.Length();) {
    offset = DisassembleInstruction(chunk, offset);
  }
}

size_t Debugger::DisassembleInstruction(const Chunk& chunk, size_t offset)
{
  std::cout << offset << " ";

  uint8_t instruction = chunk.Get(offset);
  switch (instruction) {
  case OpCode::OP_RETURN:
    return SimpleInstruction("OP_RETURN", offset);
  default:
    std::cout << "Unknown opcode " << instruction << std::endl;
    return offset + 1;
  }
}

int Debugger::SimpleInstruction(const std::string& name, size_t offset)
{
  std::cout << name << std::endl;
  return offset + 1;
}
}
