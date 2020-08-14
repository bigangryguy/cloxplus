#pragma once

#include "chunk.h"

#include <string>

namespace cloxplus {
class Debugger {
 public:
  static std::string DisassembleChunk(const Chunk& chunk,
                                       const std::string& name);
private:
  static size_t DisassembleInstruction(const Chunk& chunk,
                                       size_t offset,
                                       std::string& output);
  static size_t SimpleInstruction(const std::string& name,
                                  size_t offset,
                                  std::string& output);
};
}
