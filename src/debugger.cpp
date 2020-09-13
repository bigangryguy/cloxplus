#include "debugger.h"

#include <fmt/core.h>

namespace cloxplus {
std::string Debugger::disassembleChunk(const Chunk& chunk,
                                       const std::string& name)
{
  std::string output = fmt::format("==[ {} ]==\n", name);

  for (auto offset = 0; offset < chunk.lengthInstructions();) {
    offset = disassembleInstruction(chunk, offset, output);
    output += '\n';
  }

  return output;
}

size_t Debugger::disassembleInstruction(const Chunk& chunk,
                                        size_t offset,
                                        std::string& output)
{
  output += fmt::format("{:04d} ", offset);

  if (offset > 0 && chunk.getLine(offset) == chunk.getLine(offset-1)) {
    output += "   | ";
  } else {
    output += fmt::format("{:4d} ", chunk.getLine(offset));
  }

  auto instruction = chunk.getInstruction(offset);
  switch (instruction) {
  case OpCode::OP_RETURN:
    return simpleInstruction("OP_RETURN", offset, output);
  case OpCode::OP_CONSTANT:
    return constantInstruction("OP_CONSTANT", chunk, offset, output);
  default:
    output += fmt::format("Unknown opcode {}", instruction);
    return offset + 1;
  }
}

size_t Debugger::simpleInstruction(const std::string& name,
                                   size_t offset,
                                   std::string& output)
{
  output += fmt::format("{}", name);
  return offset + 1;
}

size_t Debugger::constantInstruction(const std::string& name,
                                     const Chunk& chunk,
                                     size_t offset,
                                     std::string& output)
{
  size_t constantOffset = chunk.getInstruction(offset + 1);
  auto constantValue = chunk.getConstant(constantOffset);
  output += fmt::format("{} {:04d} '{:g}'",
                        name, constantOffset, constantValue);
  return offset + 2;
}
}
