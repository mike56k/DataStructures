// Copyright 2020 by Isachenko Mikhail under Free Public License 1.0.0

#ifndef COMPLEX_H
#define COMPLEX_H

#include <iosfwd>

struct Complex
{
  Complex() {}
  explicit Complex(const double real);
  Complex(const double real, const double imaginary);
  bool operator==(const Complex &rhs) const noexcept
  {
    return (std::abs(re - rhs.re) <= std::numeric_limits<double>::epsilon() &&
    std::abs(im - rhs.im) <= std::numeric_limits<double>::epsilon());
  }
  bool operator!=(const Complex &rhs) const noexcept { return !operator==(rhs); }
  Complex &operator+=(const Complex &rhs) noexcept;
  Complex &operator+=(const double rhs) noexcept { return operator+=(Complex(rhs)); }
  Complex &operator-=(const Complex &rhs) noexcept;
  Complex &operator-=(const double rhs) noexcept { return operator-=(Complex(rhs)); }
  Complex &operator*=(const Complex &rhs) noexcept;
  Complex &operator*=(const double rhs) noexcept;
  Complex operator-() const;

  // can throw std::invalid_argument
  Complex &operator/=(const Complex &rhs);
  Complex &operator/=(const double rhs);
  std::ostream &writeTo(std::ostream &ostrm) const;
  std::istream &readFrom(std::istream &istrm);

  double re{0.0};
  double im{0.0};

  static const char leftBrace{'{'};
  static const char separator{','};
  static const char rightBrace{'}'};
};

Complex operator+(const Complex &lhs, const Complex &rhs) noexcept;
Complex operator+(const Complex& lhs, const double rhs) noexcept;
Complex operator-(const Complex& lhs, const double rhs) noexcept;
Complex operator-(const double lhs, const Complex &rhs) noexcept;
Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;

Complex operator/(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, const double rhs);
Complex operator/(const double lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator*(const double lhs, const Complex& rhs) noexcept;
Complex operator*(const Complex& lhs, const double rhs) noexcept;

std::ostream &operator<<(std::ostream &ostrm, const Complex &rhs);
std::istream &operator>>(std::istream &istrm, Complex &rhs);

#endif