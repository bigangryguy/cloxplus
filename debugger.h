#pragma once

#include "chunk.h"

#include <string>

namespace cloxplus {
class Debugger {
 public:
  static void DisassembleChunk(const Chunk& chunk, const std::string& name);
  static size_t DisassembleInstruction(const Chunk& chunk, size_t offset);
private:
  static int SimpleInstruction(const std::string& name, size_t offset);
};
}
