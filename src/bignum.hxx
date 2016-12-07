#pragma once

namespace bistro
{
template <typename T>
BigNum<T>::BigNum(std::size_t base)
    : base_(base)
  , positive_(true)
{}

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
  return digits_[i];
}

template <typename T>
void BigNum<T>::set_digit(index_t i, digit_t d)
{
  if (d >=  base_)
    throw std::invalid_argument("The digit is bigger than the base");
  if (i >= digits_.size())
    digits_.resize(i + 1, 0);
  digits_[i] = d;
  std::cout << "digits[" << i << "] = " << digits_[i] << "\n";
  size_t j;
  for (j = digits_.size() - 1; j > 0 && digits_[j] == 0; --j)
    continue;
  if (j == 0 && digits_[0] == 0)
    digits_.resize(0);
  else
    digits_.resize(j + 1);
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
  if (digits_.size() == 0)
    return out << b.get_digit_representation(0);
  for (auto it = digits_.rbegin(); it != digits_.rend(); ++it)
    out << b.get_digit_representation(*it);
  return out;
}

template <typename T>
typename BigNum<T>::self_t BigNum<T>::operator+(const self_t& other) const
{
  
}

template <typename T>
bool BigNum<T>::operator>(const self_t& other) const
{
  if (this->get_num_digits() == 0 && other.get_num_digits() == 0)
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
  for (i  = digits_.size(); i >= 0 && digits_[i] == other.digits_[i]; --i)
    continue;
  if (i == -1 || digits_[i] <= other.digits_[i])
    return false;
  return true;
}

template <typename T>
bool BigNum<T>::operator==(const self_t& other) const
{
  if (digits_.size() == 0 && other.digits_.size() == 0)
    return true;
  if (positive_ == other.is_positive() && digits_ == other.digits_)
    return true;
  return false;
}

template <typename T>
BigNum<T>::operator bool() const
{
  //std::cout << "operator " << digits_.size() << "\n";
  return !(*this == 0);
}

}
