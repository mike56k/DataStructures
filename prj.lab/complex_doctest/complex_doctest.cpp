// Copyright 2020 by Polevoy Dmitry under Free Public License 1.0.0

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <complex/complex.h>


#include <complex/complex.h>

#include <array>
#include <limits>
#include <sstream>
#include <utility>

constexpr double delta = std::numeric_limits<double>::epsilon();

std::array<const char*, 4> well_formated{
  "{0,1}", "{13, 3}", "{ -13, 3}", "{1.9e-3, 19.0e2}"
};
std::array<const char*, 6> bad_formated{
  "0,1", "{2/3}", "3", "2.3", "13/-3",
  "-13/-3"
};

Complex conj(const Complex& z) {
  return Complex(z.re, -z.im);
}

TEST_CASE("Complex ctor") {
  CHECK(Complex() == Complex(0.0, 0.0));
  CHECK(Complex(2.0) == Complex(2.0, 0.0));
}

TEST_CASE("Complex copy ctor") {
  Complex z(1, 2);
  Complex z_copy(z);
  CHECK(z == z_copy);
}

TEST_CASE("Complex operator=") {
  Complex z(1, 2);
  Complex z_copy;
  CHECK(z != z_copy);
  z_copy = z;
  CHECK(z == z_copy);
  z_copy = Complex(-1, 0);
  CHECK(z != z_copy);
}

TEST_CASE("Complex operator==") {
  CHECK(Complex(1) == Complex(1 + delta));
  CHECK(Complex(0, 1) == Complex(0, 1 + delta));
  CHECK(Complex(1) == Complex(1 - delta));
  CHECK(Complex(0, 1) == Complex(0, 1 - delta));
  CHECK(Complex(-1) == Complex(-1 + delta));
  CHECK(Complex(0, -1) == Complex(0, -1 + delta));
  CHECK(Complex(-1) == Complex(-1 - delta));
  CHECK(Complex(0, -1) == Complex(0, -1 - delta));
}



TEST_CASE("Complex operator!=") {
  CHECK(Complex(1) != Complex(1 + 2 * delta));
  CHECK(Complex(0, 1) != Complex(0, 1 + 2 * delta));
  CHECK(Complex(1) != Complex(1 - 2 * delta));
  CHECK(Complex(0, 1) != Complex(0, 1 - 2 * delta));
}

TEST_CASE("Complex operator>>") {
  for (const auto& str : well_formated) {
    std::istringstream istrm(str);
    Complex z;
    istrm >> z;
    CHECK(istrm.good());
  }

  for (const auto& str : bad_formated) {
    std::istringstream istrm(str);
    Complex z;
    istrm >> z;
    CHECK(istrm.fail());
  }
}

TEST_CASE("Complex conj") {
  CHECK(Complex(1) == conj(Complex(1)));
  CHECK(Complex(0, 1) == -conj(Complex(0, 1)));
}

TEST_CASE("Complex unary operator-") {
  CHECK(Complex(-1, 2) == -Complex(1, -2));
}

TEST_CASE("Complex operator+=") {
  CHECK(Complex(1, 2) == (Complex(0, 2) += 1));
  CHECK(Complex(1, 2) == (Complex(0, 2) += Complex(1)));
  CHECK(Complex(0, 1) == (Complex{} += Complex(0, 1)));
}

TEST_CASE("Complex operator+") {
  CHECK(Complex(1, 2) == (Complex(0, 2) + 1));
  CHECK(Complex(1, 2) == (Complex(0, 2) + Complex(1)));
  CHECK(Complex(0, 1) == (Complex() + Complex(0, 1)));
}

TEST_CASE("Complex operator-=") {
  CHECK(Complex(-1, 2) == (Complex(0, 2) -= 1));
  CHECK(Complex(1, 1) == (Complex(2, 1) -= Complex(1)));
  CHECK(Complex(0, -1) == (Complex() -= Complex(0, 1)));
}

TEST_CASE("Complex operator-") {
  CHECK(Complex(-1, 2) == (Complex(0, 2) - 1));
  CHECK(Complex(1, -2) == (1 - Complex(0, 2)));
  CHECK(Complex(0, 1) == (Complex(1, 1) - Complex(1)));
  CHECK(Complex(0, -1) == (Complex() - Complex(0, 1)));
}

TEST_CASE("Complex operator*=") {
  CHECK(Complex(-2, 2) == (Complex(-1, 1) *= 2));
  CHECK(Complex(-2, 2) == (Complex(1, -1) *= Complex(-2)));
  CHECK(Complex(2) == (Complex(1, 1) *= conj(Complex(1, 1))));
}

TEST_CASE("Complex operator*") {
  CHECK(Complex(2, 4) == Complex(1, 2) * 2);
  CHECK(Complex(2, 4) == 2.0 * Complex(1, 2));
  CHECK(Complex(-4, 7) == Complex(1, 2) * Complex(2, 3));
}

TEST_CASE("Complex operator/=") {
  CHECK((Complex(2, 4) /= 2) == Complex(1, 2));
  CHECK((Complex(8) /= Complex(2, 3)) == Complex(16.0 / 13, -24.0 / 13));
  CHECK((Complex(8) /= Complex(2, 3)) == 
    (Complex(8) * Complex(2, -3)) / (Complex(2, 3) * Complex(2, -3)));
}

TEST_CASE("Complex operator/") {
  CHECK(Complex(2, 4) / 2 == Complex(1, 2));
  CHECK(8 / Complex(2, 3) == Complex(16.0 / 13, -24.0 / 13));
  CHECK(Complex(8) / Complex(2, 3) ==
    (Complex(8) * Complex(2, -3)) / (Complex(2, 3) * Complex(2, -3)));
}