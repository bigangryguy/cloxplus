#pragma once

#include "common.h"

namespace cloxplus {
enum OpCode : uint8_t {
  // Operand: 1-byte offset to index of constant
  OP_CONSTANT,
  // Operand: 3-byte offset to index of constant
  OP_CONSTANT_LONG,
  // Operand: None
  OP_RETURN
};
}
