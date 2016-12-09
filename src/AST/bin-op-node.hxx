#pragma once

namespace bistro
{
  template <typename BigNum, typename Base>
  BinOpNode<BigNum, Base>::BinOpNode(node_t expr1, node_t expr2, op_t op)
    : expr1_(expr1), expr2_(expr2), op_(op)
  {}

  template <typename BigNum, typename Base>
  std::ostream& BinOpNode<BigNum, Base>::print_infix(std::ostream& out,
                                                     const base_t& b) const
  {
    expr1_->print_infix(out, b);
    Token<BigNum>::print_op(out, op_);
    expr2_->print_infix(out, b);
    return out;
  }
  template <typename BigNum, typename Base>
  std::ostream& BinOpNode<BigNum, Base>::print_pol(std::ostream& out, const base_t& b) const
  {
    Token<BigNum>::print_op(out, op_);
    out << " ";
    expr1_->print_pol(out, b);
    expr2_->print_pol(out, b);
    return out;
  }

  template <typename BigNum, typename Base>
  typename BinOpNode<BigNum, Base>::num_t BinOpNode<BigNum, Base>::eval() const
  {
    std::cerr << "BinOpNode eval\n";
    auto base10 = Base({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'});
    BigNum left = expr1_->eval()->clone();
    std::cerr << "left = ";
    left.print(std::cerr, base10);
    std::cerr << "\nright = ";

    BigNum right = expr2_->eval()->clone();
    right.print(std::cerr, base10);
    std::cerr << "\n";
    //BigNum res = left + right;
    if (op_ == Token<BigNum>::Token_id::PLUS)
      return std::make_shared<BigNum>(left + right);
    else if (op_ == Token<BigNum>::Token_id::MINUS)
      return std::make_shared<BigNum>(left - right);
    else
      throw std::invalid_argument("Operator not handled");
    /*auto res = std::make_shared<BigNum>(left + right); // Change to op
    std::cerr << "\nres = \n";
    res->print(std::cerr, base10);
    return res;*/
  }
}

