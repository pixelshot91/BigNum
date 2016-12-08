#pragma once

namespace bistro
{
  template <typename BigNum, typename Base>
  NumberNode<BigNum, Base>::NumberNode(num_t num)
    : num_(num)
  {
  }
  template <typename BigNum, typename Base>
  std::ostream& NumberNode<BigNum, Base>::print_infix(std::ostream& out,
                                    const base_t& b) const
  {
    num_->print(out, b);
    return out;
  }

  template <typename BigNum, typename Base>
  typename NumberNode<BigNum, Base>::num_t NumberNode<BigNum, Base>::eval() const
  {
    return num_;
  }
  
}

