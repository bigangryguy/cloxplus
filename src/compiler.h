#pragma once

#include "token.h"
#include "scanner.h"
#include "chunk.h"
#include "value.h"

#include <string>

namespace cloxplus {

enum class Precedence {
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

  uint8_t makeConstant(Value value);

  std::string errorAt(const Token& token, const std::string& message);
  std::string errorAtCurrent(const std::string& message);
  std::string error(const std::string& message);
};
}
