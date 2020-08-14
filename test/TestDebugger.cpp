#include <catch2/catch.hpp>

#include "../src/chunk.h"
#include "../src/debugger.h"

#include <string>

TEST_CASE("DisassembleChunk - Valid chunk", "[Debugger]") {
  cloxplus::Chunk chunk{};
  chunk.Write(cloxplus::OpCode::OP_RETURN);
  std::string expected{ "==[ Test ]==\n0 OP_RETURN\n" };
  REQUIRE(cloxplus::Debugger::DisassembleChunk(chunk, "Test") == expected);
}

TEST_CASE("DisassembleChunk - Empty chunk", "[Debugger]") {
  cloxplus::Chunk chunk{};
  std::string expected{ "==[ Test ]==\n"};
  REQUIRE(cloxplus::Debugger::DisassembleChunk(chunk, "Test") == expected);
}

TEST_CASE("DisassembleChunk - Empty name", "[Debugger]") {
  cloxplus::Chunk chunk{};
  std::string expected{ "==[  ]==\n"};
  REQUIRE(cloxplus::Debugger::DisassembleChunk(chunk, "") == expected);
}
