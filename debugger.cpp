#include "debugger.h"

#include <fmt/core.h>

namespace cloxplus {
std::string Debugger::DisassembleChunk(const Chunk& chunk,
                                       const std::string& name)
{
  std::string output = fmt::format("==[ {} ]==\n", name);

  for (auto offset = 0; offset < chunk.Length();) {
    offset = DisassembleInstruction(chunk, offset, output);
  }

  return output;
}

size_t Debugger::DisassembleInstruction(const Chunk& chunk,
                                        size_t offset,
                                        std::string& output)
{
  output += fmt::format("{} ", offset);

  uint8_t instruction = chunk.Get(offset);
  switch (instruction) {
  case OpCode::OP_RETURN:
    return SimpleInstruction("OP_RETURN", offset, output);
  default:
    output += fmt::format("Unknown opcode {}\n", instruction);
    return offset + 1;
  }
}

size_t Debugger::SimpleInstruction(const std::string& name,
                                   size_t offset,
                                   std::string& output)
{
  output += fmt::format("{}\n", name);
  return offset + 1;
}
}
