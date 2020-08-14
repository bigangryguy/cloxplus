#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../src/chunk.h"
#include "../src/debugger.h"

#include <string>
#include <fmt/core.h>

TEST_CASE("[Debugger]", "DisassembleChunk") {
  cloxplus::Chunk chunk{};
  chunk.Write(cloxplus::OpCode::OP_RETURN);
  std::string expected{ "==[ Test ]==\n0 OP_RETURN\n" };
  REQUIRE(expected == cloxplus::Debugger::DisassembleChunk(chunk, "Test"));
}
