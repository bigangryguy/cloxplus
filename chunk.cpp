#include "chunk.h"

namespace cloxplus {
void Chunk::Write(uint8_t byte) {
  code_.push_back(byte);
}
}
