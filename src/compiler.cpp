#include "compiler.h"
#include "token.h"

#include <fmt/core.h>
#include <iostream>
#include <cassert>

namespace cloxplus {
Compiler::Compiler(const std::string& source):
 m_scanner(source)
{
}

bool Compiler::compile(Chunk* chunk) {
  assert(chunk);
  m_chunk = chunk;
  advance();
  expression();
  consume(TokenType::TOKEN_EOF, "Expect end of expression.");
  endCompiler();

  return !m_hadError;
}

void Compiler::advance() {
  m_prevToken = m_currToken;

  for (;;) {
    m_currToken = m_scanner.scanToken();
    if (m_currToken.type() != TokenType::TOKEN_ERROR) {
      break;
    }

    errorAtCurrent(std::string{m_currToken.lexeme()});
  }
}

void Compiler::consume(TokenType type, const std::string& message) {
  if (m_currToken.type() == type) {
    advance();
    return;
  }

  errorAtCurrent(message);
}

void Compiler::expression() {

}

void Compiler::endCompiler() {
  emitReturn();
}

void Compiler::emitByte(uint8_t byte) {
  m_chunk->writeInstruction(byte, m_prevToken.line());
}

void Compiler::emitBytes(uint8_t byte1, uint8_t byte2) {
  emitByte(byte1);
  emitByte(byte2);
}

void Compiler::emitReturn() {
  emitByte(OpCode::OP_RETURN);
}

std::string Compiler::errorAt(const Token& token, const std::string& message) {
  if (m_panicMode) {
    return "";
  }
  m_panicMode = true;

  std::string output = fmt::format("[line {}] Error", token.line());

  if (token.type() == TokenType::TOKEN_EOF) {
    output += "\nAt end of source";
  } else if (token.type() == TokenType::TOKEN_ERROR) {
    // Nothing yet.
  } else {
    output += fmt::format(" at '{}'", token.lexeme());
  }

  output += fmt::format("\n{}", message);

  m_hadError = true;
  return output;
}

std::string Compiler::errorAtCurrent(const std::string& message) {
  return errorAt(m_currToken, message);
}

std::string Compiler::error(const std::string& message) {
  return errorAt(m_prevToken, message);
}
}
