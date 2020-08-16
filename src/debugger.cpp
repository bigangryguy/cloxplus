#include "debugger.h"

#include <fmt/core.h>

namespace cloxplus {
std::string Debugger::disassembleChunk(const Chunk& chunk,
                                       const std::string& name)
{
  std::string output = fmt::format("==[ {} ]==\n", name);

  for (auto offset = 0; offset < chunk.lengthInstructions();) {
    offset = disassembleInstruction(chunk, offset, output);
  }

  return output;
}

size_t Debugger::disassembleInstruction(const Chunk& chunk,
                                        size_t offset,
                                        std::string& output)
{
  output += fmt::format("{} ", offset);

  auto instruction = chunk.getInstruction(offset);
  switch (instruction) {
  case OpCode::OP_RETURN:
    return simpleInstruction("OP_RETURN", offset, output);
  case OpCode::OP_CONSTANT:
    return constantInstruction("OP_CONSTANT", chunk, offset, output);
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

size_t Debugger::constantInstruction(const std::string& name,
                                     const Chunk& chunk,
                                     size_t offset,
                                     std::string& output)
{
  size_t constantOffset = chunk.getInstruction(offset + 1);
  auto constantValue = chunk.getConstant(constantOffset);
  output += fmt::format("{} {} '{}'\n",
                        name, constantOffset, constantValue);
  return offset + 2;
}
}
