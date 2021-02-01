#include "rational.h"
#include <iostream>
#include <stdexcept>
using namespace std;

void Rational::reduce() noexcept
{
    int a = num(), b = denum();
    while (a)
    {
        int temp = b % a;
        b = a;
        a = temp;
    }
    if (b < 0)
        b = -b;
    num_ /= b;
    denum_ /= b;
}

Rational operator+(const Rational &lhs, const Rational &rhs) noexcept
{
    Rational sum(lhs);
    sum += rhs;
    return sum;
}

Rational operator+(const int &lhs, const Rational &rhs) noexcept
{
    return Rational(lhs) + rhs;
}

Rational operator+(const Rational &lhs, const int &rhs) noexcept
{
    return lhs + Rational(rhs);
}

Rational operator*(const Rational &lhs, const Rational &rhs) noexcept
{
    Rational mul(lhs);
    mul *= rhs;
    return mul;
}

Rational operator*(const Rational &lhs, const int &rhs) noexcept
{
    return lhs * Rational(rhs);
}

Rational operator*(const int &lhs, const Rational &rhs) noexcept
{
    return Rational(lhs) * rhs;
}

Rational operator-(const Rational &lhs, const Rational &rhs) noexcept
{
    Rational sum(lhs);
    sum -= rhs;
    return sum;
}
Rational operator-(const Rational &lhs, const int &rhs) noexcept
{
    return lhs - Rational(rhs);
}
Rational operator-(const int &lhs, const Rational &rhs) noexcept
{
    return Rational(lhs) - rhs;
}

Rational operator/(const Rational &lhs, const Rational &rhs)
{
    Rational sum(lhs);
    sum /= rhs;
    return sum;
}
Rational operator/(const int &lhs, const Rational &rhs)
{
    return Rational(lhs) / rhs;
}
Rational operator/(const Rational &lhs, const int &rhs)
{
    if (rhs == 0)
    {
        throw std::invalid_argument("Trying to divide by 0 Rational operator/(const Rational &lhs, const int &rhs)");
    }
    return lhs / Rational(rhs);
}

bool operator<(const Rational &lhs, const int &rhs) noexcept
{
    return lhs < Rational(rhs);
}
bool operator<(const int &lhs, const Rational &rhs) noexcept
{
    return Rational(lhs) < rhs;
}
bool operator>(const Rational &lhs, const int &rhs) noexcept
{
    return lhs > Rational(rhs);
}
bool operator>(const int &lhs, const Rational &rhs) noexcept
{
    return Rational(lhs) > rhs;
}
bool operator<=(const Rational &lhs, const int &rhs) noexcept
{
    return lhs <= Rational(rhs);
}
bool operator<=(const int &lhs, const Rational &rhs) noexcept
{
    return Rational(lhs) <= rhs;
}
bool operator>=(const Rational &lhs, const int &rhs) noexcept
{
    return lhs >= Rational(rhs);
}
bool operator>=(const int &lhs, const Rational &rhs) noexcept
{
    return Rational(lhs) >= rhs;
}
bool operator==(const Rational &lhs, const int &rhs) noexcept
{
    return lhs == Rational(rhs);
}

bool operator==(const int &lhs, const Rational &rhs) noexcept
{
    return Rational(lhs) == rhs;
}
bool operator!=(const Rational &lhs, const int &rhs) noexcept
{
    return lhs != Rational(rhs);
}
bool operator!=(const int &lhs, const Rational &rhs) noexcept
{
    return Rational(lhs) != rhs;
}

bool Rational::operator==(const Rational &rhs) const noexcept
{
    if (denum() == rhs.denum() && num() == rhs.num())
        return true;
    else
        return false;
}
bool Rational::operator!=(const Rational &rhs) const noexcept
{
    return (!(*this == rhs));
}
bool Rational::operator>(const Rational &rhs) const noexcept
{
    return (num() * rhs.denum() > denum() * rhs.num());
}
bool Rational::operator<(const Rational &rhs) const noexcept
{
    return (num() * rhs.denum() < denum() * rhs.num());
}
bool Rational::operator<=(const Rational &rhs) const noexcept
{
    return (num() * rhs.denum() <= denum() * rhs.num());
}
bool Rational::operator>=(const Rational &rhs) const noexcept
{
    return (num() * rhs.denum() >= denum() * rhs.num());
}



Rational &Rational::operator*=(const Rational &rhs) noexcept
{
    denum_ *= rhs.denum();
    num_ *= rhs.num();
    reduce();
    return *this;
}

Rational &Rational::operator*=(const int &rhs) noexcept
{
    *this *= Rational(rhs);
    return *this;
}

Rational &Rational::operator/=(const Rational &rhs)
{
    Rational r(num() * rhs.denum(), denum() * rhs.num());
    *this = r;
    return *this;
}

Rational &Rational::operator/=(const int &rhs)
{
    if (rhs == 0)
    {
        throw std::invalid_argument("Trying to divide by 0 Rational &Rational::operator/=(const int &rhs)");
    }
    *this /= Rational(rhs);
    return *this;
}

bool Rational::operator==(const int& rhs) const noexcept
{
  return *this == Rational(rhs);
}

bool Rational::operator!=(const int& rhs) const noexcept
{
  return *this != Rational(rhs);
}

bool Rational::operator<(const int& rhs) const noexcept
{
  return *this < Rational(rhs);
}

bool Rational::operator<=(const int& rhs) const noexcept
{
  return *this <= Rational(rhs);
}

bool Rational::operator>(const int& rhs) const noexcept
{
  return *this > Rational(rhs);
}

bool Rational::operator>=(const int& rhs) const noexcept
{
  return *this >= Rational(rhs);
}

Rational &Rational::operator-=(const Rational &rhs) noexcept
{
    Rational r(num() * rhs.denum() - rhs.num() * denum(), denum() * rhs.denum());
    *this = r;
    return *this;
}

Rational &Rational::operator-=(const int &rhs) noexcept
{
    *this -= Rational(rhs);
    return *this;
}

Rational &Rational::operator=(const int &rhs) noexcept
{
    num_ = rhs;
    denum_ = 1;
    return *this;
}
Rational Rational::operator-() const noexcept
{
  return *this * -1;
}
Rational &Rational::operator+=(const Rational &rhs) noexcept
{
    int d = denum();
    denum_ *= rhs.denum();
    num_ = num() * rhs.denum() + rhs.num() * d;
    reduce();
    return *this;
}

Rational &Rational::operator+=(const int &rhs) noexcept
{
    *this += Rational(rhs);
    return *this;
}

std::ostream &operator<<(std::ostream &ostrm, const Rational &r) noexcept
{
    return r.writeTo(ostrm);
}

std::istream &operator>>(std::istream &istrm, Rational &r) noexcept
{
    return r.readFrom(istrm);
}
ostream &Rational::writeTo(std::ostream &ostrm) const noexcept
{
    ostrm << num() << '/' << denum();
    return ostrm;
}

istream &Rational::readFrom(std::istream &istrm) noexcept
{
    char separator(0);
    char num(0);
    char den(1);
    istrm >> num >> separator >> den;
    if (istrm.good())
    {
        
        if (('/' == separator) && (num <= '9') && (num >= '0') && (den >= '1') && (den <= '9'))
        {
            num_ = int(num);
            denum_ = int(den);
            reduce();
        }
        else
        {
            istrm.setstate(std::ios_base::failbit);
        }
    }
    return istrm;
}/*
std::istream& Rational::readFrom(std::istream& istrm) noexcept
{
  char separator(0);
  int num(0);
  int den(1);

  istrm >> num;

  if (istrm.peek() == '/') {
    istrm >> separator;

    if (istrm.peek() >= '0' && istrm.peek() <= '9') {
      istrm >> den;

      if ((istrm.good() || istrm.eof()) && den > 0) { // если после ввода знаменателя в потоке могут быть символы
        numerator_ = num;
        denominator_ = den;
        reduce();
      }
      else
        istrm.setstate(std::ios_base::failbit);
    }
    else
      istrm.setstate(std::ios_base::failbit);
  }
  else
    istrm.setstate(std::ios_base::failbit);

  return istrm;
}*/
Rational::Rational(int num, int den)
{
    if (den == 0)
    {
        throw std::invalid_argument("Trying to create 0 denum() Rational::Rational(int num, int den)");
    }
    else
    {
        if (den < 0)
        {
            den = -den;
            num = -num;
        }
        num_ = num;
        denum_ = den;
        reduce();
    }
}
