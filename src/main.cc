#include <fstream>
#include <iostream>
#include <sstream>

/*
 * Headers for the example
*/

#include <cstdint>
#include <initializer_list>

#include "base.hh"
#include "bignum.hh"
#include "AST/bin-op-node.hh"
#include "AST/number-node.hh"
/*#include "AST/un-op-node.hh"*/
#include "ast-factory.hh"

#include "token.hh"

int main(int argc, char* argv[])
{
  using value_t = uint32_t;
  std::initializer_list<char> base_10 = {'o', 'u', 'd', 't', 'q'};
  using base_t = bistro::Base<value_t>;
  using bignum_t = bistro::BigNum<value_t>;

  std::ifstream in;
  //in.open("calc.ast");
  in.open("add.ast");
  if (!in.is_open())
    std::cout << "file not open\n";
  auto factory = bistro::ASTFactory<bignum_t, base_t>{};
  auto base = factory.read_base(in);
  auto ast = factory.read_AST(in, base);

    std::cout << "Build tree\n";
  auto res = ast->eval();
  std::cout << "res = ";
  res->print(std::cout, base);
  std::cout << "\n";
  //auto base = ASTFactory::read_base(in; );
  /*std::cout << base.get_base_num() << "\n";
  std::size_t base_num = base.get_base_num();
  auto b = bignum_t(base_num);
  //b.set_positive(false);
  std::cout << "b size = " << b.get_num_digits() << "\n";
  b.set_digit(0, 1);
  b.print(std::cout, base);
  std::cout << "\nb size = " << b.get_num_digits() << "\n\n";
  b.print(std::cout, base);
  b.set_digit(1, 2);
  b.print(std::cout, base);
  std::cout << "\nb size = " << b.get_num_digits() << "\n";
  std::cout << "\n";
  b.set_digit(5, 0);
  b.print(std::cout, base);
  std::cout << "\n\n";
  b.set_digit(1, 8);
  b.print(std::cout, base);
  std::cout << "\n\n";
b.set_digit(0, 0);
  b.print(std::cout, base);
  std::cout << "\n\n";
//b.set_digit(1, 0);
  b.print(std::cout, base);
  std::cout << "\n\n";
  std::cout << "get digit " << b.get_digit(1) << "\n";

  if (!b)
    std::cout << "\nequal zero\n";
  else
    std::cout << "\ndiff than zero\n";

  auto b2 = b.clone();
  b2.print(std::cout, base);
  std::cout << "\n";
  b2.set_digit(1, 1);

  if (b > b2)
    std::cout << ">";
  else
    std::cout << "<=";
  std::cout << "\n";

  b.set_digit(1, 2);
  b2.set_digit(0, 1);
  b.set_positive(false);

  std::cout << "b = ";
  b.print(std::cout, base);
  std::cout << " and b2 = ";
  b2.print(std::cout, base);
  std::cout << "\nb + b2 = ";
  (b + b2).print(std::cout, base);
  std::cout << "\n";*/

  //std::cout << b.get_digit(0) << "\n";

  /*
   * Example use of the library:

   using value_t = uint32_t;
   using base_t = bistro::Base<value_t>;
   using bignum_t = bistro::BigNum<value_t>;

   auto b = bignum_t(10);
   b.set_digit(3, 2);
   std::cout << b.get_digit(2) << "\n"
   << b.get_digit(3) << "\n"
   << b.get_num_digits() << "\n";
   b.set_digit(3, 0);
   std::cout << b.get_num_digits() << "\n";
   try
   {
   b.get_digit(0);
   } catch (const std::out_of_range& e)
   {
   std::cerr << "Out of range: " << e.what() << '\n';
   }
   auto base = base_t{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

   std::ifstream ss("num.tes");


   auto bptr = std::make_shared<bignum_t>(ss, base);

   auto num = std::make_shared<bistro::NumberNode<bignum_t, base_t>>(bptr);
   auto minus = std::make_shared<bistro::UnOpNode<bignum_t, base_t>>(num,
   bistro::UnOpType::MINUS);
   auto plus = bistro::BinOpNode<bignum_t, base_t>(num, minus,
   bistro::BinOpType::PLUS);
   plus.print_infix(std::cout, base) << '\n';
   plus.print_pol(std::cout, base) << '\n';
   plus.eval()->print(std::cout, base) << '\n';

   std::ifstream in("test.ast");
   auto factory = bistro::ASTFactory<bignum_t, base_t>{};
   auto ast_base = factory.read(in);
   ast_base.first->print_infix(std::cout, ast_base.second) << '\n';
   ast_base.first->eval()->print(std::cout, ast_base.second) << '\n';

*/

  /*using value_t = int;
    using base_t = bistro::Base<value_t>;
    using bignum_t = bistro::BigNum<value_t>;

    if (argc < 2)
    {
    std::cout << "Usage: " << argv[0] << " <file>\n";
    return 2;
    }

  // Create a ifstream with file "test.ast".
  std::ifstream in(argv[1]);

  if (!in.is_open())
  {
  std::cerr << "Cannot open file: " << argv[1] << '\n';
  return 3;
  }

  try
  {
  // Create the ASTFactory
  auto factory = bistro::ASTFactory<bignum_t, base_t>{};

  // Create the AST and get the root node
  auto ast_base = factory.read(in);

  // Print the expression in infix representation
  ast_base.first->print_infix(std::cout, ast_base.second) << '\n';

  // Print the evaluation of the expression
  ast_base.first->eval()->print(std::cout, ast_base.second) << '\n';
  }
  catch (std::exception &e)
  {
  std::cerr << e.what() << '\n';
  return 1;
  }*/

  return 0;
}
