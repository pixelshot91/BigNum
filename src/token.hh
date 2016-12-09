#pragma once

#include <memory>
#include <queue>
#include <string>
#include <fstream>

namespace bistro
{
template <typename BigNum>
class Token
{
  public:
    enum Token_id
    {
      NUMBER,
      PLUS,
      MINUS,
      STAR,
      SLASH,
      PERCENT,
      L_PAR,
      R_PAR,
      NB_TOKEN
    };
    /*std::string token_id_name[8] =
    {
      "number",
      "+",
      "-",
      "*",
      "/",
      "%",
      "(",
      ")"
    };*/

    using tokens_t = std::queue<Token>;
    using num_t = std::shared_ptr<BigNum>;
    Token(Token_id id, num_t num);
    static void eat(tokens_t& tokens, Token_id id);
    Token_id get_id() const;
    num_t get_num() const;
    //std::ostream& print(std::ostream& out, const base_t& b) const;
    //void print();
    static std::ostream& print_op(std::ostream& out, Token_id op);

  private:
    Token_id id_;
    num_t num_;
};
}

#include "token.hxx"
