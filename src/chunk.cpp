#include "chunk.h"

namespace cloxplus {
void Chunk::Write(uint8_t byte) {
  code_.push_back(byte);
}

size_t Chunk::Length() const noexcept {
  return code_.size();
}

uint8_t Chunk::Get(size_t offset) const {
  return code_[offset];
}
}
