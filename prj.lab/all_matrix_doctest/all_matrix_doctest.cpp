#include <matrixvs/matrixvs.h>
#include <matrixds/matrixds.h>
#include <matrixls/matrixls.h>
#include <matrixvr/matrixvr.h>
#include <matrixdr/matrixdr.h>
#include <matrixlr/matrixlr.h>


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>


TEST_CASE_TEMPLATE("Test Construction", T, MatrixDr, MatrixDs, MatrixLr, MatrixVs, MatrixLs, MatrixVr) {
  int r = 2, c = 3;
  T M1(0, 0), M2;
  T a(c, r);
  bool flag = true;
  if (a.rowCount() != r || a.colCount() != c) flag = false;
  try {
    for (int i = 0; i < r; ++i) { for (int j = 0; j < c; ++j) if (a.at(i, j) != 0) flag = false; }
  }
  catch (std::out_of_range& out_of) { std::cerr << out_of.what() << std::endl; flag = false; }
  catch (std::invalid_argument& inv) { std::cerr << inv.what() << std::endl; flag = false; }
  CHECK(flag == true);
}

TEST_CASE_TEMPLATE("Test Copy", T, MatrixDr, MatrixDs, MatrixLr, MatrixVs, MatrixLs, MatrixVr) {
  T a(3, 2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      a.at(i, j) = i + 2 + j;
    }
  }
  T b(a);
  T c; c = a;
  CHECK(a == b);
  CHECK(a == c);
  T a1 = a;
  a1 = a1;
  CHECK(a1 == a);
}

TEST_CASE_TEMPLATE("Test Multiply", T,MatrixDr, MatrixDs, MatrixLr, MatrixVs, MatrixLs, MatrixVr) {
  T a(3, 2), b(1, 3), c(1, 2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      a.at(i, j) = i + 2 + j;
    }
  }
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 1; ++j) {
      b.at(i, j) = 2 + i;
    }
  }
  c.at(0, 0) = 29;
  c.at(1, 0) = 38;
  a.multiply(b);
  try {
    CHECK(a == c);
  }
  catch (std::exception& ex) { std::cerr << ex.what() << std::endl; }
}

TEST_CASE_TEMPLATE("Test Transpose", T, MatrixDr, MatrixDs, MatrixLr, MatrixVs, MatrixLs, MatrixVr) {
  T a(3, 2), b(2, 3);
  for (std::ptrdiff_t i = 0; i < 2; ++i) {
    for (std::ptrdiff_t j = 0; j < 3; ++j) {
      a.at(i, j) = i + j;
      b.at(j, i) = i + j;
    }
  }
  a.transpose();
  CHECK(a == b);
}

TEST_CASE_TEMPLATE("Test Swap", T, MatrixVs, MatrixDr, MatrixDs, MatrixLr, MatrixLs, MatrixVr) {
  SUBCASE("Swap Rows") {
    T a(3, 2), b(3, 2);
    float c = 1;
    for (std::ptrdiff_t i = 0; i < 2; ++i) {
      for (std::ptrdiff_t j = 0; j < 3; ++j) {
        a.at(i, j) = c;
        ++c;
      }
    }
    c = 1;
    for (std::ptrdiff_t i = 1; i >= 0; --i) {
      for (std::ptrdiff_t j = 0; j < 3; ++j) {
        b.at(i, j) = c;
        ++c;
      }
    }
    a.swapRows(0, 1);
    CHECK(a == b);
  }
  SUBCASE("Swap Columns") {
    T a(3, 2), b(3, 2);
    float c = 1;
    for (std::ptrdiff_t i = 0; i < 3; ++i) {
      for (std::ptrdiff_t j = 0; j < 2; ++j) {
        a.at(j, i) = c;
        ++c;
      }
    }
    c = 1;
    for (std::ptrdiff_t i = 2; i >= 0; --i) {
      for (std::ptrdiff_t j = 0; j < 2; ++j) {
        b.at(j, i) = c;
        ++c;
      }
    }
    a.swapColumns(0, 2);
    CHECK(a == b);
  }
}

//
//int main(){
//    MatrixVs a(2, 3);
//    for(int i = 0; i < 3; ++i){
//        for(int j = 0; j < 2; ++j){
//            a.at(i, j) = 2;
//        }
//    }
//    a.at(1, 1) = 1;
//    std::cout << a << std::endl;
//    a.transpose();
//    std::cout << a;
//}