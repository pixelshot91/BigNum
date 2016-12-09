#pragma once

#include <ios>
#include <fstream>

//#include "bin-op-node.hh"

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
      std::cerr << "number ";
    else if (t.first == PLUS)
      std::cerr << "PLUS ";
    else
      std::cerr << "UNDIFINED ";
  }*/
  std::cerr << "Parse Begin\n";
  auto ast = parse_expr(tokens);
  return ast;
}

/*template <typename BigNum, typename Base>
void ASTFactory<BigNum, Base>::eat(tokens_t tokens, Token_id id)
{
  auto front_id = std::get<Token_id>(tokens.front());
  if (front_id != id)
  {
    std::stringstream ss;
    ss << "Grammar error : unexpected " << token_id_name[front_id] << ", expected " << token_id_name[id];
    throw std::domain_error(ss.str());
  }
  tokens.pop();
}*/

template <typename BigNum, typename Base>
typename ASTFactory<BigNum, Base>::node_t ASTFactory<BigNum, Base>::parse_expr(tokens_t& tokens)
{
  node_t term = parse_term(tokens); //
  auto op = tokens.front().get_id();
  if (op == token_t::Token_id::PLUS)
  {
    token_t::eat(tokens, token_t::Token_id::PLUS);
    node_t term2 = parse_expr(tokens);
    auto expr = std::make_shared<BinOpNode<BigNum, Base>>(term, term2, op);
    return expr;
  }
  else if (op == token_t::Token_id::MINUS)
  {
    token_t::eat(tokens, token_t::Token_id::MINUS);
    node_t term2 = parse_expr(tokens);
    auto expr = std::make_shared<BinOpNode<BigNum, Base>>(term, term2, op);
    return expr;
  }
  return term;
}

template <typename BigNum, typename Base>
typename ASTFactory<BigNum, Base>::node_t ASTFactory<BigNum, Base>::parse_term(tokens_t& tokens)
{
  node_t term = parse_factor(tokens); //
  auto op = tokens.front().get_id();
  if (op == token_t::Token_id::STAR)
  {
    token_t::eat(tokens, token_t::Token_id::STAR);
    node_t term2 = parse_term(tokens);
    auto expr = std::make_shared<BinOpNode<BigNum, Base>>(term, term2, op);
    return expr;
  }
  else if (op == token_t::Token_id::SLASH)
  {
    token_t::eat(tokens, token_t::Token_id::SLASH);
    node_t term2 = parse_term(tokens);
    auto expr = std::make_shared<BinOpNode<BigNum, Base>>(term, term2, op);
    return expr;
  }
  return term;
}

template <typename BigNum, typename Base>
typename ASTFactory<BigNum, Base>::node_t ASTFactory<BigNum, Base>::parse_factor(tokens_t& tokens)
{
  std::shared_ptr<BigNum> num_ptr = tokens.front().get_num();
  node_t res = std::make_shared<NumberNode<BigNum, Base>>(NumberNode<BigNum, Base>(num_ptr));
  tokens.pop();
  return res;
}

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
      tokens.push(token_t(token_t::Token_id::PLUS, nullptr));
    else if (c == '-')
      tokens.push(token_t(token_t::Token_id::MINUS, nullptr));
    else if (c == '*')
      tokens.push(token_t(token_t::Token_id::STAR, nullptr));
    else if (c == '/')
      tokens.push(token_t(token_t::Token_id::SLASH, nullptr));
    else if (c == '%')
      tokens.push(token_t(token_t::Token_id::PERCENT, nullptr));
    else if (c == '(')
      tokens.push(token_t(token_t::Token_id::L_PAR, nullptr));
    else if (c == ')')
      tokens.push(token_t(token_t::Token_id::R_PAR, nullptr));
    else if (b.is_digit(c))
    {
      in.putback(c);
      auto num = std::make_shared<BigNum>(BigNum(in, b));
auto base10 = Base({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'});
    std::cerr << "BigNum = \n";
    num->print(std::cerr, base10);
    std::cerr << "\n";

      tokens.push(token_t(token_t::Token_id::NUMBER, num));
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

