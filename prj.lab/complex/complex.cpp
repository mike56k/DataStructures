#include <iostream>
#include <sstream>
#include <stdexcept>
#include "complex.h"
#include <limits>

std::ostream &operator<<(std::ostream &ostrm, const Complex &rhs)
{
  return rhs.writeTo(ostrm);
}

std::istream &operator>>(std::istream &istrm, Complex &rhs)
{
  return rhs.readFrom(istrm);
}

Complex::Complex(const double real)
  : Complex(real, 0.0)
{
}

Complex::Complex(const double real, const double imaginary)
  : re(real), im(imaginary)
{
}

Complex &Complex::operator+=(const Complex &rhs) noexcept
{
  re += rhs.re;
  im += rhs.im;
  return *this;
}
Complex &Complex::operator-=(const Complex &rhs) noexcept
{
  re -= rhs.re;
  im -= rhs.im;
  return *this;
}
Complex &Complex::operator*=(const Complex &rhs) noexcept
{
  double re1 = re;
  re = re * rhs.re - im * rhs.im;
  im = re1 * rhs.im + im * rhs.re;
  return *this;
}
Complex operator+(const Complex &lhs, const Complex &rhs) noexcept
{
  Complex sum(lhs);
  sum += rhs;
  return sum;
}

Complex operator+(const Complex& lhs, const double rhs) noexcept
{
  Complex sum(lhs);
  sum += rhs;
  return sum;
}

Complex operator-(const Complex& lhs, const double rhs) noexcept
{
  Complex t = Complex(lhs);
  t -= rhs;
  return t;
}

Complex operator-(const double lhs, const Complex& rhs) noexcept
{
  Complex t = Complex(lhs);
  t -= rhs;
  return t;
}

Complex operator-(const Complex &lhs, const Complex &rhs) noexcept
{
  return Complex(lhs.re - rhs.re, lhs.im - rhs.im);
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
  Complex t = Complex(lhs);
  t/=rhs;
  return t;
}

Complex operator/(const Complex& lhs, const double rhs)
{
  Complex t = Complex(lhs);
  t /= rhs;
  return t;
}

Complex operator/(const double lhs, const Complex& rhs)
{
  Complex t = Complex(double(lhs));
  t /= rhs;
  return t;
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept
{
  Complex t = Complex(lhs);
  t *= rhs;
  return t;
}

Complex operator*(const double lhs, const Complex& rhs) noexcept
{
  Complex t = Complex(lhs);
  t *= rhs;
  return t;
}

Complex operator*(const Complex& lhs, const double rhs) noexcept
{
  Complex t = Complex(lhs);
  t *= rhs;
  return t;
}

Complex &Complex::operator*=(const double rhs) noexcept
{
  re *= rhs;
  im *= rhs;
  return *this;
}
Complex Complex::operator-() const
{
  return Complex(-re, -im);
}
Complex& Complex::operator/=(const Complex& rhs)
{

  double re1 = ((re * rhs.re) + (im * rhs.im))/(rhs.re * rhs.re + rhs.im * rhs.im);
  im = ((rhs.re * im) - (re * rhs.im))/(rhs.re * rhs.re + rhs.im * rhs.im);
  re = re1;
  return *this;
}
Complex &Complex::operator/=(const double rhs)
{
  if (rhs < 2 * std::numeric_limits<double>::epsilon())
  {
    throw std::invalid_argument("Divizion by zero in Complex::operator/=(const double)");
  }
  re /= rhs;
  im /= rhs;
  return *this;
}
std::ostream &Complex::writeTo(std::ostream &ostrm) const
{
  ostrm << leftBrace << re << separator << im << rightBrace;
  return ostrm;
}

std::istream &Complex::readFrom(std::istream &istrm)
{
  char leftBrace(0);
  double real(0.0);
  char comma(0);
  double imaganary(0.0);
  char rightBrace(0);
  istrm >> leftBrace >> real >> comma >> imaganary >> rightBrace;
  if (istrm.good())
  {
    if ((Complex::leftBrace == leftBrace) && (Complex::separator == comma) &&
      (Complex::rightBrace == rightBrace))
    {
      re = real;
      im = imaganary;
    }
    else
    {
      istrm.setstate(std::ios_base::failbit);
    }
  }
  return istrm;
}