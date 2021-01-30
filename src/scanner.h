#pragma once

#include <string>

namespace cloxplus {
class Token;
enum class TokenType;

class Scanner {
public:
  explicit Scanner(const std::string& source);

  [[nodiscard]] Token scanToken();
private:
  [[nodiscard]] std::string_view currentLexeme() const;
  [[nodiscard]] Token makeToken(TokenType type) const;
  [[nodiscard]] Token errorToken(const std::string& message) const;
  [[nodiscard]] bool match(char expected);
  void skipWhitespace();
  Token string();
  Token number();
  Token identifier();
  [[nodiscard]] static TokenType identifierType(std::string_view identifier) ;
  [[nodiscard]] bool isAtEnd() const;
  [[nodiscard]] static bool isDigit(char c);
  [[nodiscard]] static bool isAlpha(char c);

  std::string m_source;
  const size_t m_lengthSource;
  size_t m_startPosition = 0;
  size_t m_currentPosition = 0;
  int m_line = 1;
};
}
