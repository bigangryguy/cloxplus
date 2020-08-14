#include <catch2/catch.hpp>

#include "../src/chunk.h"
#include "../src/debugger.h"

#include <string>

TEST_CASE("disassembleChunk - Valid chunk", "[Debugger]") {
  cloxplus::Chunk chunk{};
  chunk.write(cloxplus::OpCode::OP_RETURN);
  std::string expected{ "==[ Test ]==\n0 OP_RETURN\n" };
  REQUIRE(cloxplus::Debugger::disassembleChunk(chunk, "Test") == expected);
}

TEST_CASE("disassembleChunk - Empty chunk", "[Debugger]") {
  cloxplus::Chunk chunk{};
  std::string expected{ "==[ Test ]==\n"};
  REQUIRE(cloxplus::Debugger::disassembleChunk(chunk, "Test") == expected);
}

TEST_CASE("disassembleChunk - Empty name", "[Debugger]") {
  cloxplus::Chunk chunk{};
  std::string expected{ "==[  ]==\n"};
  REQUIRE(cloxplus::Debugger::disassembleChunk(chunk, "") == expected);
}
