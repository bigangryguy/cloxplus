#include <catch2/catch.hpp>

#include "../src/chunk.h"
#include "../src/debugger.h"

#include <string>

TEST_CASE("disassembleChunk - Valid chunk", "[Debugger]") {
  cloxplus::Chunk chunk{};
  chunk.writeInstruction(cloxplus::OpCode::OP_RETURN);
  uint8_t index = chunk.writeConstant(3.14);
  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT);
  chunk.writeInstruction(static_cast<uint8_t>(index));
  std::string expected{ "==[ Test ]==\n0 OP_RETURN\n1 OP_CONSTANT 0 '3.14'\n" };
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
