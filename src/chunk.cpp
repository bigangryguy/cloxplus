#include "chunk.h"

namespace cloxplus {
void Chunk::writeInstruction(uint8_t instruction, int line) {
  m_instructions.push_back(instruction);
  m_lines.push_back(line);
}

size_t Chunk::writeConstant(Value value) {
  m_constants.push_back(value);
  return m_constants.size() - 1;
}

size_t Chunk::lengthInstructions() const noexcept {
  return m_instructions.size();
}

size_t Chunk::lengthConstants() const noexcept {
  return m_constants.size();
}

uint8_t Chunk::getInstruction(size_t offset) const {
  return m_instructions[offset];
}

Value Chunk::getConstant(size_t offset) const {
  return m_constants[offset];
}

int Chunk::getLine(size_t offset) const {
  return m_lines[offset];
}
}
