#pragma once

#include "common.h"
#include "opcode.h"
#include <vector>

namespace cloxplus {
class Chunk {
 public:
  void write(uint8_t byte);
  size_t length() const noexcept;
  uint8_t get(size_t offset) const;

 private:
  std::vector<uint8_t> m_code;
};
}