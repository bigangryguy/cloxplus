#pragma once

#include "token.h"
#include "scanner.h"
#include "chunk.h"

#include <string>

namespace cloxplus {

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
  void endCompiler();

  void emitByte(uint8_t byte);
  void emitBytes(uint8_t byte1, uint8_t byte2);
  void emitReturn();

  std::string errorAt(const Token& token, const std::string& message);
  std::string errorAtCurrent(const std::string& message);
  std::string error(const std::string& message);
};
}
