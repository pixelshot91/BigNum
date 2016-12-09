#pragma once

#include <sstream>
#include <string>

namespace bistro
{
template <typename T>
BigNum<T>::BigNum(std::size_t base)
  : base_(base)
  , positive_(true)
{
}

template <typename T>
template <typename Base>
BigNum<T>::BigNum(std::ifstream& in, const Base& b)
  : base_(b.get_base_num())
    , positive_(true)
{
  if (!b.is_digit(in.peek()))
  {
    std::stringstream ss;
    ss << "Cannot initialize BigNum from file that does not contain digit in "
          "first position\n"
       << "Character is " << in.peek();
    throw std::length_error(ss.str());
  }
  std::vector<char> v;
  while (b.is_digit(in.peek()))
  {
    v.push_back(in.get());
  }
  for (size_t i = 0; i < v.size(); ++i)
  {
    //b.get_char_value(v[i]);
    set_digit(i, b.get_char_value(v[v.size() - 1 - i]));
  }
}

template <typename T>
typename BigNum<T>::self_t BigNum<T>::clone() const
{
  auto clone = BigNum(base_);
  clone.digits_ = digits_;
  clone.positive_ = positive_;
  return clone;
}

template <typename T>
typename BigNum<T>::index_t BigNum<T>::get_num_digits() const
{
  if (digits_.size() == 0)
    return 1;
  return digits_.size() + !positive_;
}

template <typename T>
typename BigNum<T>::digit_t BigNum<T>::get_digit(index_t i) const
{
  if (i >= digits_.size())
    throw std::out_of_range("Get digit has been called with a index over the "
                            "number of digits in the BigNum");
  return digits_[i];
}

template <typename T>
void BigNum<T>::set_digit(index_t i, digit_t d)
{
  if (d >= base_)
  {
    std::stringstream ss;
    ss << "Cannot set digit " << i << " to " << d
       << " because this BigNum is expressed in base " << base_;
    throw std::invalid_argument(ss.str());
  }
  if (i >= digits_.size())
    digits_.resize(i + 1, 0);
  digits_[i] = d;
  std::cerr << "digits[" << i << "] = " << digits_[i] << "\n";
  shrink();
}

template <typename T>
bool BigNum<T>::is_positive() const
{
  return positive_;
}

template <typename T>
void BigNum<T>::set_positive(bool p)
{
  positive_ = p;
}

template <typename T>
template <typename Base>
std::ostream& BigNum<T>::print(std::ostream& out, const Base& b) const
{
  if (base_ != b.get_base_num())
  {
    std::stringstream ss;
    ss << "Cannot print a BigNum expressed in base " << base_ << " with a base "
       << b.get_base_num();
    throw std::invalid_argument(ss.str());
  }

  if (digits_.size() == 0)
    return out << b.get_digit_representation(0);
  if (!positive_)
    std::cout << "-";
  for (auto it = digits_.rbegin(); it != digits_.rend(); ++it)
    out << b.get_digit_representation(*it);
  return out;
}

template <typename T>
void BigNum<T>::check_same_base(const self_t& other) const
{
  if (base_ != other.base_)
    throw std::invalid_argument("The size of the base given as argument is "
                                "different than the size of the base of the "
                                "BigNum to print");
}

template <typename T>
typename BigNum<T>::self_t BigNum<T>::operator+(const self_t& other) const
{
  check_same_base(other);
  if (positive_ == other.positive_)
  {
    BigNum result = raw_add(other);
    result.positive_ = positive_;
    return result;
  }
  if (positive_) // P + N
  {
    BigNum result = raw_sub(other);
    return result;
  }
  else // N + P
  {
    std::cerr << "N + P -> -(|N| - P)\n";
    BigNum result = raw_sub(other);
    result.positive_ = !result.positive_;
    return result;
  }
}

template <typename T>
typename BigNum<T>::self_t BigNum<T>::operator-(const self_t& other) const
{
  std::cerr << "operaor-\n";
  check_same_base(other);
  if (positive_ == other.positive_)
  {
    BigNum result = raw_sub(other);
    if (!positive_)
      result.positive_ = !result.positive_;
    return result;
  }
  if (positive_) // P - N
    return raw_add(other);
  else // N - P
  {
    BigNum result = raw_add(other);
    result.positive_ = !result.positive_;
    return result;
  }
}

template <typename T>
typename BigNum<T>::self_t& BigNum<T>::operator+=(const self_t& other)
{
  check_same_base(other);
  *this = *this + other;
  return *this;
}

template <typename T>
typename BigNum<T>::self_t& BigNum<T>::operator-=(const self_t& other)
{
  check_same_base(other);
  *this = *this - other;
  return *this;
}

template <typename T>
typename BigNum<T>::self_t BigNum<T>::raw_add(const self_t& other) const
{
  bool carry = false;
  auto max_len = std::max<size_t>(digits_.size(), other.digits_.size());
  BigNum res(base_);
  res.digits_.resize(max_len + 1, 0);
  for (size_t i = 0; i < max_len || carry; ++i)
  {
    auto r = get_value(i) + other.get_value(i) + carry;
    carry = false;
    if (r >= base_)
    {
      r -= base_;
      carry = true;
    }
    res.digits_[i] = r;
  }
  res.shrink();
  return res;
}

template <typename T>
typename BigNum<T>::self_t BigNum<T>::abs() const
{
  BigNum abs = clone();
  abs.positive_ = true;
  return abs;
}


template <typename T>
typename BigNum<T>::self_t BigNum<T>::raw_sub(const self_t& other) const
{
  /*std::cout << "\nthis = ";
  for (auto i : digits_)
    std::cout << i << " ";
  std::cout << "\nother = ";
  for (auto i : other.digits_)
    std::cout << i << " ";
  std::cout << "\n";

  if (this->abs() > other.abs())
    std::cout << "this > other\n";
  else
    std::cout << "this <= other\n";*/
  const BigNum& n1 = (this->abs() > other.abs()) ? *this : other;
  const BigNum& n2 = (this->abs() > other.abs()) ? other : *this;
  std::cerr << "\nn1 = ";
  for (auto i : n1.digits_)
    std::cerr << i << " ";
  std::cerr << "\nn2 = ";
  for (auto i : n2.digits_)
    std::cerr << i << " ";
  std::cerr << "\n";
  bool carry = false;
  auto max_len = std::max<size_t>(digits_.size(), other.digits_.size());
  BigNum res(base_);
  res.digits_.resize(max_len + 1, 0);
  for (size_t i = 0; i < max_len; ++i)
  {
    auto r = n1.get_value(i) - n2.get_value(i) - carry;
    //std::cout << "i = " << i << " r = " << r << "\n";
    if (n1.get_value(i) < n2.get_value(i) + carry)
    {
      r += base_;
      //std::cout << "new r = " << r << "\n";
      carry = true;
    }
    else
      carry = false;
    //std::cout << "carry = " << carry << "\n";
    res.digits_[i] = r;
  }
  if (!(this->abs() > other.abs()))
    res.positive_ = !res.positive_;
  res.shrink();
  return res;
}


template <typename T>
bool BigNum<T>::operator>(const self_t& other) const
{
  if (base_ != other.base_)
    throw std::invalid_argument(
      "Try to compare two BigNum expressed in different base");
  if (digits_.size() == 0 && other.digits_.size() == 0)
    return false;
  if (is_positive() != other.is_positive())
    return is_positive();
  if (get_num_digits() != other.get_num_digits())
  {
    if (get_num_digits() > other.get_num_digits())
      return is_positive();
    return !is_positive();
  }
  ssize_t i;
  for (i = digits_.size(); i >= 0 && digits_[i] == other.digits_[i]; --i)
    continue;
  if (i >= 0 && digits_[i] > other.digits_[i])
    return true;
  return false;
}

template <typename T>
bool BigNum<T>::operator==(const self_t& other) const
{
  if (base_ != other.base_)
    throw std::invalid_argument(
      "Try to compare two BigNum expressed in different base");

  if (digits_.size() == 0 && other.digits_.size() == 0)
    return true;
  if (positive_ == other.is_positive() && digits_ == other.digits_)
    return true;
  return false;
}

template <typename T>
BigNum<T>::operator bool() const
{
  // std::cout << "operator " << digits_.size() << "\n";
  return digits_.size() != 0;
}

template <typename T>
void BigNum<T>::shrink()
{
  size_t j;
  for (j = digits_.size() - 1; j > 0 && digits_[j] == 0; --j)
    continue;
  if (j == 0 && digits_[0] == 0)
    digits_.resize(0);
  else
    digits_.resize(j + 1);
}

template <typename T>
T BigNum<T>::get_value(index_t i) const
{
  if (i < digits_.size())
    return digits_[i];
  return 0;
}
}
