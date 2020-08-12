#pragma once

#include "common.h"
#include <vector>

namespace cloxplus {
enum OpCode : uint8_t { OP_RETURN };

class Chunk {
 public:
  void Write(uint8_t byte);

 private:
  std::vector<uint8_t> code_;
};
}