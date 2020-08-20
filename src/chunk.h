#pragma once

#include "common.h"
#include "opcode.h"
#include "value.h"
#include <vector>

namespace cloxplus {
class Chunk {
 public:
  void writeInstruction(uint8_t instruction, int line);
  [[nodiscard]] size_t writeConstant(Value value);
  size_t lengthInstructions() const noexcept;
  size_t lengthConstants() const noexcept;
  [[nodiscard]] uint8_t getInstruction(size_t offset) const;
  [[nodiscard]] Value getConstant(size_t offset) const;
  [[nodiscard]] int getLine(size_t offset) const;

 private:
  std::vector<uint8_t> m_instructions{};
  std::vector<Value> m_constants{};
  std::vector<int> m_lines{};
};
}