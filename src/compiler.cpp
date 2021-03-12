#include "compiler.h"
#include "token.h"

#include <fmt/core.h>
#include <iostream>
#include <cassert>
#include <utility>

namespace cloxplus {
ParseRule::ParseRule(ParseFn prefix, ParseFn infix, Precedence precedence)
    : m_prefix(std::move(prefix)), m_infix(std::move(infix)), m_precedence(precedence)
{
}

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
  parsePrecedence(Precedence::PREC_ASSIGNMENT);
}

void Compiler::parsePrecedence(Precedence precedence) {

}

void Compiler::endCompiler() {
  emitReturn();
}

void Compiler::number() {
  double value = strtod(std::string{m_prevToken.lexeme()}.c_str(), nullptr);
  emitConstant(value);
}

void Compiler::grouping() {
  expression();
  consume(TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
}

void Compiler::unary() {
  TokenType operatorType = m_prevToken.type();

  parsePrecedence(Precedence::PREC_UNARY);

  switch (operatorType) {
  case TokenType::TOKEN_MINUS: emitByte(static_cast<uint8_t>(OpCode::OP_NEGATE)); break;
  default:
    return;
  }
}

void Compiler::binary() {
  TokenType operatorType = m_prevToken.type();

  ParseRule* rule = getRule(operatorType);
  parsePrecedence(static_cast<Precedence>(rule->precedence() + 1));

  switch (operatorType) {
  case TokenType::TOKEN_PLUS: emitByte(OpCode::OP_ADD); break;
  case TokenType::TOKEN_MINUS: emitByte(OpCode::OP_SUBTRACT); break;
  case TokenType::TOKEN_STAR: emitByte(OpCode::OP_MULTIPLY); break;
  case TokenType::TOKEN_SLASH: emitByte(OpCode::OP_DIVIDE); break;
  default:
    return;
  }
}

void Compiler::emitByte(uint8_t byte) {
  m_chunk->writeInstruction(byte, m_prevToken.line());
}

void Compiler::emitBytes(uint8_t byte1, uint8_t byte2) {
  emitByte(byte1);
  emitByte(byte2);
}

void Compiler::emitConstant(Value value) {
  emitBytes(OpCode::OP_CONSTANT, makeConstant(value));
}

void Compiler::emitReturn() {
  emitByte(OpCode::OP_RETURN);
}

ParseRule* Compiler::getRule(TokenType type) {
  return &rules[type];
}

uint8_t Compiler::makeConstant(Value value) {
  size_t constant = m_chunk->writeConstant(value);
  if (constant > UINT8_MAX) {
    error("Too many constants in one chunk.");
    return 0;
  }

  return static_cast<uint8_t>(constant);
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
