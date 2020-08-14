#include <catch2/catch.hpp>

#include "../src/chunk.h"

TEST_CASE("write", "[Chunk]") {
  cloxplus::Chunk chunk{};
  REQUIRE_NOTHROW(chunk.write(cloxplus::OpCode::OP_RETURN));
}

TEST_CASE("length", "[Chunk]") {
  cloxplus::Chunk chunk{};

  SECTION("Single write") {
    chunk.write(cloxplus::OpCode::OP_RETURN);
    REQUIRE(chunk.length() == 1);
  }

  SECTION("Three writes") {
    chunk.write(cloxplus::OpCode::OP_RETURN);
    chunk.write(cloxplus::OpCode::OP_RETURN);
    chunk.write(cloxplus::OpCode::OP_RETURN);
    REQUIRE(chunk.length() == 3);
  }
}

TEST_CASE("get", "[Chunk]") {
  cloxplus::Chunk chunk{};

  SECTION("Single value") {
    chunk.write(cloxplus::OpCode::OP_RETURN);
    auto expected = cloxplus::OpCode::OP_RETURN;
    REQUIRE(chunk.get(0) == expected);
  }

  SECTION("Three values") {
    chunk.write(13);
    chunk.write(21);
    chunk.write(55);
    auto expected = 21;
    REQUIRE(chunk.get(1) == expected);
  }
}
