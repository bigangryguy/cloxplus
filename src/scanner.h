#pragma once

#include "token.h"

#include <string>

namespace cloxplus {
class Token;

class Scanner {
public:
  explicit Scanner(const std::string& source);

  [[nodiscard]] Token scanToken();

  [[nodiscard]] static bool isDigit(char c);
  [[nodiscard]] static bool isAlpha(char c);
private:
  [[nodiscard]] std::string_view currentLexeme() const;
  [[nodiscard]] Token makeToken(TokenType type) const;
  [[nodiscard]] Token errorToken(const std::string& message) const;
  [[nodiscard]] bool match(char expected);
  void skipWhitespace();
  Token string();
  Token number();
  Token identifier();
  [[nodiscard]] bool isAtEnd() const;

  [[nodiscard]] TokenType identifierType(std::string_view identifier);
  [[nodiscard]] TokenType checkKeyword(int start, int length,
                                       const std::string& rest, TokenType type);

  std::string m_source;
  const size_t m_lengthSource;
  size_t m_startPosition = -1;
  size_t m_currentPosition = -1;
  int m_line = 1;
};
}
