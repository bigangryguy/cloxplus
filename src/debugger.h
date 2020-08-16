#pragma once

#include "chunk.h"

#include <string>

namespace cloxplus {
class Debugger {
 public:
  static std::string disassembleChunk(const Chunk& chunk,
                                       const std::string& name);
private:
  static size_t disassembleInstruction(const Chunk& chunk,
                                       size_t offset,
                                       std::string& output);

  static size_t simpleInstruction(const std::string& name,
                                  size_t offset,
                                  std::string& output);

  static size_t constantInstruction(const std::string& name,
                                    const Chunk& chunk,
                                    size_t offset,
                                    std::string& output);
};
}
