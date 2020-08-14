#pragma once

#include "common.h"
#include "opcode.h"
#include <vector>

namespace cloxplus {
class Chunk {
 public:
  void Write(uint8_t byte);
  size_t Length() const noexcept;
  uint8_t Get(size_t offset) const;

 private:
  std::vector<uint8_t> code_;
};
}