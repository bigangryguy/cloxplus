#include "scanner.h"
#include "token.h"

namespace cloxplus{
Scanner::Scanner(const std::string& source) :
  m_source(source), m_lengthSource(source.length())
{
}

std::string_view Scanner::currentLexeme() const {
  std::string_view lexeme(m_source);
  lexeme.remove_prefix(m_startPosition);
  lexeme.remove_suffix(m_lengthSource - m_currentPosition - 1);
  return lexeme;
}

Token Scanner::makeToken(TokenType type) const {
  return Token(type, currentLexeme(), m_line);
}

Token Scanner::scanToken() {
  if (isAtEnd()) {
    return makeToken(TokenType::TOKEN_EOF);
  }

  m_currentPosition++;
  skipWhitespace();
  m_startPosition = m_currentPosition;

  char c = m_source[m_currentPosition];
  if (isAlpha(c)) {
    return identifier();
  }
  if (isDigit(c)) {
    return number();
  }
  switch (c) {
  case '(': return makeToken(TokenType::TOKEN_LEFT_PAREN);
  case ')': return makeToken(TokenType::TOKEN_RIGHT_PAREN);
  case '{': return makeToken(TokenType::TOKEN_LEFT_BRACE);
  case '}': return makeToken(TokenType::TOKEN_RIGHT_BRACE);
  case ';': return makeToken(TokenType::TOKEN_SEMICOLON);
  case ',': return makeToken(TokenType::TOKEN_COMMA);
  case '.': return makeToken(TokenType::TOKEN_DOT);
  case '-': return makeToken(TokenType::TOKEN_MINUS);
  case '+': return makeToken(TokenType::TOKEN_PLUS);
  case '/': return makeToken(TokenType::TOKEN_SLASH);
  case '*': return makeToken(TokenType::TOKEN_STAR);
  case '!':
    return makeToken(match('=') ? TokenType::TOKEN_BANG_EQUAL : TokenType::TOKEN_BANG);
  case '=':
    return makeToken(match('=') ? TokenType::TOKEN_EQUAL_EQUAL : TokenType::TOKEN_EQUAL);
  case '<':
    return makeToken(match('=') ? TokenType::TOKEN_LESS_EQUAL : TokenType::TOKEN_LESS);
  case '>':
    return makeToken(match('=') ? TokenType::TOKEN_GREATER_EQUAL : TokenType::TOKEN_GREATER);
  case '"': return string();
  default: return errorToken("Unexpected character.");
  }
}

Token Scanner::errorToken(const std::string& message) const {
  return Token(TokenType::TOKEN_ERROR, std::string_view(message), m_line);
}

bool Scanner::match(char expected) {
  if (isAtEnd()) {
    return false;
  }

  if (m_source[m_currentPosition+1] != expected) {
    return false;
  }

  m_currentPosition++;
  return true;
}

void Scanner::skipWhitespace() {
  for (;;) {
    char c = m_source[m_currentPosition];
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
      m_currentPosition++;
      break;
    case '\n': { // Increment line number when newline is found
      m_line++;
      m_currentPosition++;
      break;
    }
    case '/': { // Process comments, if found
      if (m_source[m_currentPosition+1] == '/') {
        while (m_source[m_currentPosition] != '\n' && !isAtEnd()) {
          m_currentPosition++;
        }
      } else {
        return;
      }
      break;
    }
    default:
      return;
    }
  }
}

Token Scanner::string() {
  //m_startPosition = m_currentPosition;
  m_currentPosition++;
  while (m_source[m_currentPosition] != '"' && !isAtEnd()) {
    if (m_source[m_currentPosition] == '\n') {
      m_line++;
    }
    m_currentPosition++;
  }

  if (isAtEnd()) {
    return errorToken("Unterminated string.");
  }

  //m_currentPosition++;
  return makeToken(TokenType::TOKEN_STRING);
}

Token Scanner::number() {
  while (isDigit(m_source[m_currentPosition])) {
    m_currentPosition++;
  }

  if (m_source[m_currentPosition] == '.' && isDigit(m_source[m_currentPosition+1])) {
    m_currentPosition++;

    while(isDigit(m_source[m_currentPosition])) {
      m_currentPosition++;
    }
  }
  m_currentPosition--;

  return makeToken(TokenType::TOKEN_NUMBER);
}

Token Scanner::identifier() {
  while (isAlpha(m_source[m_currentPosition]) || isDigit(m_source[m_currentPosition])) {
    m_currentPosition++;
  }
  m_currentPosition--;

  return makeToken(identifierType(currentLexeme()));
}

TokenType Scanner::checkKeyword(int start, int length, const std::string& rest, TokenType type) {
  if (m_currentPosition - m_startPosition + 1 == start + length &&
      m_source.substr(m_startPosition + start, length) == rest) {
    return type;
  }

  return TokenType::TOKEN_IDENTIFIER;
}

TokenType Scanner::identifierType(std::string_view identifier) {
  switch (m_source[m_startPosition]) {
  case 'a': return checkKeyword(1, 2, "nd", TokenType::TOKEN_AND);
  case 'c': return checkKeyword(1, 4, "lass", TokenType::TOKEN_CLASS);
  case 'e': return checkKeyword(1, 3, "lse", TokenType::TOKEN_ELSE);
  case 'f':
    if (m_currentPosition - m_startPosition > 1) {
      switch (m_source[m_startPosition+1]) {
      case 'a': return checkKeyword(2, 3, "lse", TokenType::TOKEN_FALSE);
      case 'o': return checkKeyword(2, 1, "r", TokenType::TOKEN_FOR);
      case 'u': return checkKeyword(2, 1, "n", TokenType::TOKEN_FUN);
      }
    }
    break;
  case 'i': return checkKeyword(1, 1, "f", TokenType::TOKEN_IF);
  case 'n': return checkKeyword(1, 2, "il", TokenType::TOKEN_NIL);
  case 'o': return checkKeyword(1, 1, "r", TokenType::TOKEN_OR);
  case 'p': return checkKeyword(1, 4, "rint", TokenType::TOKEN_PRINT);
  case 'r': return checkKeyword(1, 5, "eturn", TokenType::TOKEN_RETURN);
  case 's': return checkKeyword(1, 4, "uper", TokenType::TOKEN_SUPER);
  case 't':
    if (m_currentPosition - m_startPosition > 1) {
      switch (m_source[m_startPosition+1]) {
      case 'h': return checkKeyword(2, 2, "is", TokenType::TOKEN_THIS);
      case 'r': return checkKeyword(2, 2, "ue", TokenType::TOKEN_TRUE);
      }
    }
    break;
  case 'v': return checkKeyword(1, 2, "ar", TokenType::TOKEN_VAR);
  case 'w': return checkKeyword(1, 4, "hile", TokenType::TOKEN_WHILE);
  }
  return TokenType::TOKEN_IDENTIFIER;
}

bool Scanner::isAtEnd() const {
  return m_currentPosition == m_lengthSource;
}

bool Scanner::isDigit(char c) {
  return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) {
  return (c >= 'a' && c <= 'z') ||
      (c >= 'A' && c <= 'Z') ||
      c == '_';
}
}
