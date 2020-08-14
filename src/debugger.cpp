#include "debugger.h"

#include <fmt/core.h>

namespace cloxplus {
std::string Debugger::disassembleChunk(const Chunk& chunk,
                                       const std::string& name)
{
  std::string output = fmt::format("==[ {} ]==\n", name);

  for (auto offset = 0; offset < chunk.length();) {
    offset = disassembleInstruction(chunk, offset, output);
  }

  return output;
}

size_t Debugger::disassembleInstruction(const Chunk& chunk,
                                        size_t offset,
                                        std::string& output)
{
  output += fmt::format("{} ", offset);

  uint8_t instruction = chunk.get(offset);
  switch (instruction) {
  case OpCode::OP_RETURN:
    return simpleInstruction("OP_RETURN", offset, output);
  default:
    output += fmt::format("Unknown opcode {}\n", instruction);
    return offset + 1;
  }
}

size_t Debugger::simpleInstruction(const std::string& name,
                                   size_t offset,
                                   std::string& output)
{
  output += fmt::format("{}\n", name);
  return offset + 1;
}
}
