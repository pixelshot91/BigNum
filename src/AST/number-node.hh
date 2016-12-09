#pragma once

//#include "ast-node.hh"

namespace bistro
{
  template <typename BigNum, typename Base>
  class NumberNode : public ASTNode<BigNum, Base>
  {
  public:
    using base_t = typename ASTNode<BigNum, Base>::base_t;
    using num_t = typename ASTNode<BigNum, Base>::num_t;

    NumberNode(num_t num);
    std::ostream& print_infix(std::ostream& out, const base_t& b) const override;
    std::ostream& print_pol(std::ostream& out, const base_t& b) const override;
    num_t eval() const override;

  private:
    num_t num_;
  };
}

#include "number-node.hxx"
