#include "chunk.h"

namespace cloxplus {
void Chunk::write(uint8_t byte) { m_code.push_back(byte);
}

size_t Chunk::length() const noexcept {
  return m_code.size();
}

uint8_t Chunk::get(size_t offset) const {
  return m_code[offset];
}
}
