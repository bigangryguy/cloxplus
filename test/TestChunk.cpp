#include <catch2/catch.hpp>

#include "../src/chunk.h"

TEST_CASE("Chunk - writeInstruction", "[Chunk]") {
  cloxplus::Chunk chunk{};
  REQUIRE_NOTHROW(chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 1));
}

TEST_CASE("Chunk - writeConstant", "[Chunk]") {
  cloxplus::Chunk chunk{};
  REQUIRE_NOTHROW(chunk.writeConstant(3.14));
}

TEST_CASE("Chunk - lengthInstructions", "[Chunk]") {
  cloxplus::Chunk chunk{};

  SECTION("Single writeInstruction") {
    chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 1);
    REQUIRE(chunk.lengthInstructions() == 1);
  }

  SECTION("Three writeInstruction") {
    chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 1);
    chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 2);
    chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 3);
    REQUIRE(chunk.lengthInstructions() == 3);
  }
}

TEST_CASE("Chunk - lengthConstants", "[Chunk]") {
  cloxplus::Chunk chunk{};

  SECTION("Single writeConstant") {
    uint8_t index = chunk.writeConstant(3.14);
    REQUIRE(chunk.lengthConstants() == 1);
    REQUIRE(index == 0);
  }

  SECTION("Three writeConstant") {
    uint8_t index = chunk.writeConstant(3.14);
    REQUIRE(index == 0);
    index = chunk.writeConstant(42.0);
    REQUIRE(index == 1);
    index = chunk.writeConstant(99.9);
    REQUIRE(index == 2);
    REQUIRE(chunk.lengthConstants() == 3);
  }
}

TEST_CASE("Chunk - getInstruction", "[Chunk]") {
  cloxplus::Chunk chunk{};

  SECTION("Single value") {
    chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 1);
    auto expected = cloxplus::OpCode::OP_RETURN;
    REQUIRE(chunk.getInstruction(0) == expected);
  }

  SECTION("Three values") {
    chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 1);
    chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 2);
    chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 3);
    auto expected = cloxplus::OpCode::OP_CONSTANT;
    REQUIRE(chunk.getInstruction(1) == expected);
  }
}

TEST_CASE("Chunk - getConstant", "[Chunk]") {
  cloxplus::Chunk chunk{};

  SECTION("Single value") {
    uint8_t index = chunk.writeConstant(3.14);
    auto expected = 3.14;
    REQUIRE(chunk.getConstant(0) == expected);
  }

  SECTION("Three values") {
    uint8_t index = chunk.writeConstant(3.14);
    index = chunk.writeConstant(42.0);
    index = chunk.writeConstant(99.9);
    auto expected = 42.0;
    REQUIRE(chunk.getConstant(1) == expected);
  }
}

TEST_CASE("Chunk - getLine", "[Chunk]") {
  cloxplus::Chunk chunk{};

  SECTION("Single line") {
    chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 1);
    auto expected = 1;
    REQUIRE(chunk.getLine(0) == expected);
  }

  SECTION("Three values") {
    chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 1);
    chunk.writeInstruction(cloxplus::OpCode::OP_CONSTANT, 2);
    chunk.writeInstruction(cloxplus::OpCode::OP_RETURN, 3);
    auto expected = 2;
    REQUIRE(chunk.getLine(1) == expected);
  }
}
