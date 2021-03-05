#include "token.h"

namespace cloxplus {
Token::Token(TokenType type, std::string_view lexeme, int line, int start) :
  m_type(type), m_lexeme(lexeme), m_line(line), m_start(start)
{
}
}
