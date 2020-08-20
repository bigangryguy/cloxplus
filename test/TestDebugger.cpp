#include <catch2/catch.hpp>

#include "../src/chunk.h"
#include "../src/debugger.h"

#include <string>

TEST_CASE("disassembleChunk - Valid chunk", "[Debugger]") {
  cloxplus::Chunk chunk{};
  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 1);
  chunk.writeInstruction(chunk.writeConstant(3.14), 1);
  chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 1);
  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 2);
  chunk.writeInstruction(chunk.writeConstant(42.0), 2);
  chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 2);
  std::string expected{
      R"debug(==[ Test ]==
0000    1 OP_CONSTANT 0000 '3.14'
0002    | OP_RETURN
0003    2 OP_CONSTANT 0001 '42'
0005    | OP_RETURN
)debug"
  };
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
