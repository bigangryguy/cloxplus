#pragma once

#include <memory>

namespace cloxplus {
class Chunk;

class VM {
public:
private:
  std::unique_ptr<Chunk> m_chunk;

};
}
