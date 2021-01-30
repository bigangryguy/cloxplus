#include "token.h"

namespace cloxplus {
Token::Token(TokenType type, std::string_view lexeme, int line) :
  m_type(type), m_lexeme(lexeme), m_length(lexeme.length()), m_line(line)
{
}
}
