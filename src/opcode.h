#pragma once

#include "common.h"

namespace cloxplus {
enum OpCode : uint8_t {
  // Operand: 1-byte offset to index of constant
  OP_CONSTANT,
  // Operator: Adds the preceding two numeric values
  OP_ADD,
  // Operator: Subtracts the last numeric value from the next to last
  // numeric value
  OP_SUBTRACT,
  // Operator: Multiplies the preceding two numeric values
  OP_MULTIPLY,
  // Operator: Divides the last numeric value by the next to last
  // numeric value
  OP_DIVIDE,
  // Operator: Negates the preceding numeric value
  OP_NEGATE,
  // Operand: 3-byte offset to index of constant
  OP_CONSTANT_LONG,
  // Operand: None
  OP_RETURN
};
}
