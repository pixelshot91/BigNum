#include "token.hh"

#include <sstream>
#include <fstream>

namespace bistro
{
template <typename BigNum>
Token<BigNum>::Token(Token_id id, num_t num)
: id_(id)
  , num_(num)
  {}

template <typename BigNum>
void Token<BigNum>::eat(tokens_t& tokens, Token_id id)
{
  auto front_id = tokens.front().get_id();
  if (front_id != id)
  {
    std::stringstream ss;
    std::string token_id_name[8] =
    {
      "number",
      "+",
      "-",
      "*",
      "/",
      "%",
      "(",
      ")"
    };

    ss << "Grammar error : unexpected " << token_id_name[front_id] << ", expected " << token_id_name[id];
    throw std::domain_error(ss.str());
  }
  tokens.pop();
}

template <typename BigNum>
std::ostream& Token<BigNum>::print_op(std::ostream& out, Token_id op)
{
  std::string token_id_name[8] =
    {
      "number",
      "+",
      "-",
      "*",
      "/",
      "%",
      "(",
      ")"
    };

  out << token_id_name[op];
  return out; 
}

template <typename BigNum>
typename Token<BigNum>::Token_id Token<BigNum>::get_id() const
{
  return id_;
}

template <typename BigNum>
typename Token<BigNum>::num_t Token<BigNum>::get_num() const
{
  return num_;
}

}

