#pragma once

#include <ios>
#include <fstream>

namespace bistro
{
/*template <typename BigNum, typename Base>
std::pair<node_t, base_t> ASTFactory<BigNum, Base>::read(std::ifstream& in)
{
  
}*/

template <typename BigNum, typename Base>
typename ASTFactory<BigNum, Base>::base_t
ASTFactory<BigNum, Base>::read_base(std::ifstream& in)
{
  if (!in.is_open())
    throw std::invalid_argument("Try to read base from empty file");
  std::string line;
  std::getline(in, line);
  unsigned base_len = std::stoi(line);
  std::getline(in, line);
  if (line.size() != base_len)
  {
    std::stringstream ss;
    ss << "Invalid input file. The base is expected to contain " << base_len
       << " characters, " << line.size() << " were given";
    throw std::domain_error(ss.str());
  }
  Base base;
  for (auto c : line)
    base.add_digit(c);
  return base;
}

template <typename BigNum, typename Base>
typename ASTFactory<BigNum, Base>::node_t ASTFactory<BigNum, Base>::read_AST(std::ifstream& in, const Base& b)
{
  auto tokens = lexer(in, b);
  /*for (auto t : tokens)
  {
    if (t.first == NUMBER)
      std::cout << "number ";
    else if (t.first == PLUS)
      std::cout << "PLUS ";
    else
      std::cout << "UNDIFINED ";
  }*/
  /*auto ast = parse_expr(in);
  return ast;*/
}

/*template <typename BigNum, typename Base>
typename ASTFactory<BigNum, Base>::node_t ASTFactory<BigNum, Base>::parse_expr(v_token_t tokens)
{
  auto term_1 = parse_term(tokens);
  if (in.peek() == '+')
    eat('+')

}*/


template <typename BigNum, typename Base>
typename ASTFactory<BigNum, Base>::tokens_t ASTFactory<BigNum, Base>::lexer(std::ifstream& in, const Base& b)
{
  tokens_t tokens;
  if (!in.good())
    throw std::invalid_argument("Input file is not readable");
  int c = in.get();
  while (in.eof() == false)
  {
    if (c == '+')
      tokens.push(token_t(PLUS, nullptr));
    else if (c == '-')
      tokens.push(token_t(MINUS, nullptr));
    else if (c == '*')
      tokens.push(token_t(STAR, nullptr));
    else if (c == '/')
      tokens.push(token_t(SLASH, nullptr));
    else if (c == '%')
      tokens.push(token_t(PERCENT, nullptr));
    else if (c == '(')
      tokens.push(token_t(L_PAR, nullptr));
    else if (c == ')')
      tokens.push(token_t(R_PAR, nullptr));
    else if (b.is_digit(c))
    {
      in.putback(c);
      auto num = std::make_shared<BigNum>(BigNum(in, b));
      tokens.push(token_t(NUMBER, num));
    }
    else
    {
      std::stringstream ss;
      ss << "In " << __FUNCTION__ <<": Invalid character in expression to evaluate\n"
         << "Character is " << static_cast<char>(c) << " (" << c << ")"
         << ". It's neither an operator nor a digit define in the base";
      throw std::domain_error(ss.str());
    }
    c = in.get();
  }
  return tokens;
}

}

