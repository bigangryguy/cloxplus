#pragma once

#include "interpretresult.h"

#include <memory>

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

  InterpretResult run();
};
}
