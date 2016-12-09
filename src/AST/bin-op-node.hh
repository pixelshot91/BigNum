#pragma once

#include "ast-node.hh"
#include "token.hh"

namespace bistro
{
  template <typename BigNum, typename Base>
  class BinOpNode : public ASTNode<BigNum, Base>
  {
  public:
    using base_t = typename ASTNode<BigNum, Base>::base_t;
    using num_t = typename ASTNode<BigNum, Base>::num_t;
    using op_t = typename Token<BigNum>::Token_id;
    using node_t = typename ASTNode<BigNum, Base>::node_t;

    BinOpNode(node_t expr1, node_t expr2, op_t op);
    std::ostream& print_infix(std::ostream& out, const base_t& b) const override;
    std::ostream& print_pol(std::ostream&, const base_t&) const override;
    num_t eval() const override;

  private:
    node_t expr1_;
    node_t expr2_;
    op_t op_;
  };
}

#include "bin-op-node.hxx"
