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
  typename BinOpNode<BigNum, Base>::num_t BinOpNode<BigNum, Base>::eval() const
  {
    std::cout << "BinOpNode eval\n";
    auto base10 = Base({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'});
    BigNum left = expr1_->eval()->clone();
    std::cout << "left = ";
    left.print(std::cout, base10);
    std::cout << "\nright = ";

    BigNum right = expr2_->eval()->clone();
    right.print(std::cout, base10);
    std::cout << "\n";
    //BigNum res = left + right;
    auto res = std::make_shared<BigNum>(left + right); // Change to op
    std::cout << "\nres = \n";
    res->print(std::cout, base10);
    return res;
  }
}

