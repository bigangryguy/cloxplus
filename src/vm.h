#pragma once

#include "interpretresult.h"
#include "value.h"

#include <memory>
#include <vector>

namespace cloxplus {
class Chunk;

class VM {
public:
  VM();
  ~VM();

  InterpretResult interpret(std::unique_ptr<Chunk> chunk);
private:
  std::unique_ptr<Chunk> m_chunk;
  size_t m_ip;
  // Using std::vector instead of std::stack to make printing
  // debugger output much simpler
  std::vector<Value> m_stack;

  InterpretResult run();
};
}
