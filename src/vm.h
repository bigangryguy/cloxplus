#pragma once

#include "interpretresult.h"
#include "value.h"
#include "chunk.h"

#include <vector>

namespace cloxplus {
class VM {
public:
  VM();
  ~VM();

  InterpretResult interpret(const std::string& source);
private:
  Chunk m_chunk{};
  size_t m_ip;
  // Using std::vector instead of std::stack to make printing
  // debugger output much simpler
  std::vector<Value> m_stack;

  InterpretResult run();
};
}
