// Copyright 2020 by Isachenko Mikhail under Free Public License 1.0.0

#ifndef RATIONAL_H_20201010
#define RATIONAL_H_20201010
#include <iosfwd>

class Rational {
public:
  Rational() = default;
  Rational(const Rational&) = default;
  explicit Rational(const int num) : num_(num), denum_(1) {};
  Rational(const int num, const int denum);
  Rational& operator=(const Rational&) = default;
  Rational& operator=(const int&) noexcept;
  int num() const { return num_; }
  int denum() const { return denum_; }

  Rational operator-() const  noexcept;
  Rational& operator+=(const Rational& rhs) noexcept;
  Rational& operator-=(const Rational& rhs) noexcept;
  Rational& operator*=(const Rational& rhs) noexcept;
  Rational& operator/=(const Rational& rhs);

  bool operator==(const Rational& rhs) const noexcept;
  bool operator!=(const Rational& rhs) const noexcept;
  bool operator<(const Rational& rhs) const noexcept;
  bool operator<=(const Rational& rhs) const noexcept;
  bool operator>(const Rational& rhs) const noexcept;
  bool operator>=(const Rational& rhs) const noexcept;

  Rational& operator+=(const int& rhs) noexcept;
  Rational& operator-=(const int& rhs) noexcept;
  Rational& operator*=(const int& rhs) noexcept;
  Rational& operator/=(const int& rhs);

  bool operator==(const int& rhs) const noexcept;
  bool operator!=(const int& rhs) const noexcept;
  bool operator<(const int& rhs) const noexcept;
  bool operator<=(const int& rhs) const noexcept;
  bool operator>(const int& rhs) const noexcept;
  bool operator>=(const int& rhs) const noexcept;

  std::istream& readFrom(std::istream& istrm) noexcept;
  std::ostream& writeTo(std::ostream& ostrm) const noexcept;
  
  void reduce() noexcept;
private:
  int num_ = 0;
  int denum_ = 0;
};

 std::istream& operator>>(std::istream& istrm, Rational& r) noexcept;
 std::ostream& operator<<(std::ostream& ostrm, const Rational& r) noexcept;

 Rational operator+(const Rational& lhs, const Rational& rhs) noexcept;
 Rational operator-(const Rational& lhs, const Rational& rhs) noexcept;
 Rational operator*(const Rational& lhs, const Rational& rhs) noexcept;
 Rational operator/(const Rational& lhs, const Rational& rhs);

#endif