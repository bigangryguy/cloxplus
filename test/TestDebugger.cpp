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
  chunk.writeInstruction(cloxplus::OpCode::OP_NEGATE, 2);
  chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 2);

  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 3);
  chunk.writeInstruction(chunk.writeConstant(10), 3);
  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 3);
  chunk.writeInstruction(chunk.writeConstant(6), 3);
  chunk.writeInstruction(cloxplus::OpCode::OP_ADD, 3);
  chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 3);

  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 4);
  chunk.writeInstruction(chunk.writeConstant(12.2), 4);
  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 4);
  chunk.writeInstruction(chunk.writeConstant(8.4), 4);
  chunk.writeInstruction(cloxplus::OpCode::OP_SUBTRACT, 4);
  chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 4);

  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 5);
  chunk.writeInstruction(chunk.writeConstant(9), 5);
  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 5);
  chunk.writeInstruction(chunk.writeConstant(7), 5);
  chunk.writeInstruction(cloxplus::OpCode::OP_MULTIPLY, 5);
  chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 5);

  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 6);
  chunk.writeInstruction(chunk.writeConstant(11.1), 6);
  chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 6);
  chunk.writeInstruction(chunk.writeConstant(2.2), 6);
  chunk.writeInstruction(cloxplus::OpCode::OP_DIVIDE, 6);
  chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 6);

  std::string expected{
      R"debug(==[ Test ]==
0000    1 OP_CONSTANT 0000 '3.14'
0002    | OP_RETURN
0003    2 OP_CONSTANT 0001 '42'
0005    | OP_NEGATE
0006    | OP_RETURN
0007    3 OP_CONSTANT 0002 '10'
0009    | OP_CONSTANT 0003 '6'
0011    | OP_ADD
0012    | OP_RETURN
0013    4 OP_CONSTANT 0004 '12.2'
0015    | OP_CONSTANT 0005 '8.4'
0017    | OP_SUBTRACT
0018    | OP_RETURN
0019    5 OP_CONSTANT 0006 '9'
0021    | OP_CONSTANT 0007 '7'
0023    | OP_MULTIPLY
0024    | OP_RETURN
0025    6 OP_CONSTANT 0008 '11.1'
0027    | OP_CONSTANT 0009 '2.2'
0029    | OP_DIVIDE
0030    | OP_RETURN
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
