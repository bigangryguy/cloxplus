#include "value.h"

#include <fmt/core.h>

namespace cloxplus {
void printValue(Value value)
{
  std::cout << fmt::format("{}", value) << std::endl;
}
}
