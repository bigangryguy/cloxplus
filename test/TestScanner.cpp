#include <catch2/catch_all.hpp>

#include "../src/scanner.h"
#include "../src/token.h"

#include <string_view>
#include <vector>
#include <iostream>

TEST_CASE("isDigit", "[Scanner]") {
  const std::string digits{"0123456789"};
  for (const char c : digits) {
    REQUIRE(cloxplus::Scanner::isDigit(c));
  }

  for (char c = 'a'; c <= 'z'; c++) {
    REQUIRE_FALSE(cloxplus::Scanner::isDigit(c));
  }

  for (char c = 'A'; c <= 'Z'; c++) {
    REQUIRE_FALSE(cloxplus::Scanner::isDigit(c));
  }

  REQUIRE_FALSE(cloxplus::Scanner::isDigit('_'));
}

TEST_CASE("isAlpha", "[Scanner]") {
  for (char c = 'a'; c <= 'z'; c++) {
    REQUIRE(cloxplus::Scanner::isAlpha(c));
  }

  for (char c = 'A'; c <= 'Z'; c++) {
    REQUIRE(cloxplus::Scanner::isAlpha(c));
  }

  REQUIRE(cloxplus::Scanner::isAlpha('_'));

  const std::string digits{"0123456789"};
  for (const char c : digits) {
    REQUIRE_FALSE(cloxplus::Scanner::isAlpha(c));
  }
}

TEST_CASE("scanToken", "[Scanner]") {
  const std::string source{
      "(){};,.-+/*!=! ===<=<>=>\n\"Hello, world\",\nx2 = 12.73\n"
      "and class else if\nfalse for fun nil or print return super this true var while\n34"
  };

  cloxplus::Scanner scanner(source);
  int index = 0;
  std::vector<cloxplus::Token> expected = {
      cloxplus::Token(cloxplus::TokenType::TOKEN_LEFT_PAREN, "(", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_RIGHT_PAREN, ")", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_LEFT_BRACE, "{", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_RIGHT_BRACE, "}", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_SEMICOLON, ";", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_COMMA, ",", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_DOT, ".", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_MINUS, "-", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_PLUS, "+", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_SLASH, "/", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_STAR, "*", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_BANG_EQUAL, "!=", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_BANG, "!", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_EQUAL_EQUAL, "==", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_EQUAL, "=", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_LESS_EQUAL, "<=", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_LESS, "<", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_GREATER_EQUAL, ">=", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_GREATER, ">", 1),
      cloxplus::Token(cloxplus::TokenType::TOKEN_STRING, "\"Hello, world\"", 2),
      cloxplus::Token(cloxplus::TokenType::TOKEN_COMMA, ",", 2),
      cloxplus::Token(cloxplus::TokenType::TOKEN_IDENTIFIER, "x2", 3),
      cloxplus::Token(cloxplus::TokenType::TOKEN_EQUAL,"=", 3),
      cloxplus::Token(cloxplus::TokenType::TOKEN_NUMBER, "12.73", 3),
      cloxplus::Token(cloxplus::TokenType::TOKEN_AND, "and", 4),
      cloxplus::Token(cloxplus::TokenType::TOKEN_CLASS, "class", 4),
      cloxplus::Token(cloxplus::TokenType::TOKEN_ELSE, "else", 4),
      cloxplus::Token(cloxplus::TokenType::TOKEN_IF, "if", 4),
      cloxplus::Token(cloxplus::TokenType::TOKEN_FALSE, "false", 5),
      cloxplus::Token(cloxplus::TokenType::TOKEN_FOR, "for", 5),
      cloxplus::Token(cloxplus::TokenType::TOKEN_FUN, "fun", 5),
      cloxplus::Token(cloxplus::TokenType::TOKEN_NIL, "nil", 5),
      cloxplus::Token(cloxplus::TokenType::TOKEN_OR, "or", 5),
      cloxplus::Token(cloxplus::TokenType::TOKEN_PRINT, "print", 5),
      cloxplus::Token(cloxplus::TokenType::TOKEN_RETURN, "return", 5),
      cloxplus::Token(cloxplus::TokenType::TOKEN_SUPER, "super", 5),
      cloxplus::Token(cloxplus::TokenType::TOKEN_THIS, "this", 5),
      cloxplus::Token(cloxplus::TokenType::TOKEN_TRUE, "true", 5),
      cloxplus::Token(cloxplus::TokenType::TOKEN_VAR, "var", 5),
      cloxplus::Token(cloxplus::TokenType::TOKEN_WHILE, "while", 5),
      cloxplus::Token(cloxplus::TokenType::TOKEN_NUMBER, "34", 6),
  };
  do {
    cloxplus::Token token = scanner.scanToken();
    REQUIRE(token.type() == expected[index].type());
    REQUIRE(token.lexeme().compare(expected[index].lexeme()) == 0);
    REQUIRE(token.line() == expected[index].line());
    index++;
  } while (index < expected.size());
}
