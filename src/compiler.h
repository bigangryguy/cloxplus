#pragma once

#include "token.h"
#include "scanner.h"
#include "chunk.h"
#include "value.h"

#include <string>
#include <vector>
#include <functional>

namespace cloxplus {

enum Precedence : int {
  PREC_NONE,
  PREC_ASSIGNMENT,  // =
  PREC_OR,          // or
  PREC_AND,         // and
  PREC_EQUALITY,    // == !=
  PREC_COMPARISON,  // < > <= >=
  PREC_TERM,        // + -
  PREC_FACTOR,      // * /
  PREC_UNARY,       // ! -
  PREC_CALL,        // . ()
  PREC_PRIMARY
};

using ParseFn = std::function<void()>;

class ParseRule {
public:
  ParseRule(ParseFn prefix, ParseFn infix, Precedence precedence);

  [[nodiscard]] std::function<void()> prefix() const { return m_prefix; }
  [[nodiscard]] std::function<void()> infix() const { return m_infix; }
  [[nodiscard]] Precedence precedence() const { return m_precedence; }
private:
  std::function<void()> m_prefix;
  std::function<void()> m_infix;
  Precedence m_precedence;
};

class Compiler {
public:
  explicit Compiler(const std::string& source);

  bool compile(Chunk* chunk);
private:
  Scanner m_scanner;
  Chunk* m_chunk = nullptr;
  Token m_currToken = Token(TokenType::TOKEN_EOF, "", 0, 0);
  Token m_prevToken = Token(TokenType::TOKEN_EOF, "", 0, 0);
  bool m_hadError = false;
  bool m_panicMode = false;
  std::vector<ParseRule> rules = {
      /*[TOKEN_LEFT_PAREN]   */ ParseRule(ParseFn([this] { grouping(); }), nullptr, PREC_NONE),
      /*[TOKEN_RIGHT_PAREN]  */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_LEFT_BRACE]   */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_RIGHT_BRACE]  */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_COMMA]        */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_DOT]          */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_MINUS]        */ ParseRule(ParseFn([this] { unary(); }), ParseFn([this] { binary(); }), PREC_TERM),
      /*[TOKEN_PLUS]         */ ParseRule(nullptr, ParseFn([this] { binary(); }), PREC_TERM),
      /*[TOKEN_SEMICOLON]    */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_SLASH]        */ ParseRule(nullptr, ParseFn([this] { binary(); }), PREC_FACTOR),
      /*[TOKEN_STAR]         */ ParseRule(nullptr, ParseFn([this] { binary(); }), PREC_FACTOR),
      /*[TOKEN_BANG]         */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_BANG_EQUAL]   */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_EQUAL]        */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_EQUAL_EQUAL]  */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_GREATER]      */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_GREATER_EQUAL]*/ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_LESS]         */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_LESS_EQUAL]   */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_IDENTIFIER]   */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_STRING]       */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_NUMBER]       */ ParseRule(ParseFn([this] { number(); }), nullptr, PREC_NONE),
      /*[TOKEN_AND]          */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_CLASS]        */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_ELSE]         */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_FALSE]        */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_FOR]          */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_FUN]          */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_IF]           */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_NIL]          */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_OR]           */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_PRINT]        */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_RETURN]       */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_SUPER]        */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_THIS]         */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_TRUE]         */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_VAR]          */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_WHILE]        */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_ERROR]        */ ParseRule(nullptr,     nullptr,   PREC_NONE),
      /*[TOKEN_EOF]          */ ParseRule(nullptr,     nullptr,   PREC_NONE),
  };

  void advance();
  void consume(TokenType type, const std::string& message);
  void expression();
  void parsePrecedence(Precedence precedence);
  void endCompiler();

  void number();
  void grouping();
  void unary();
  void binary();

  void emitByte(uint8_t byte);
  void emitBytes(uint8_t byte1, uint8_t byte2);
  void emitConstant(Value value);
  void emitReturn();

  ParseRule* getRule(TokenType type);

  uint8_t makeConstant(Value value);

  std::string errorAt(const Token& token, const std::string& message);
  std::string errorAtCurrent(const std::string& message);
  std::string error(const std::string& message);
};
}
