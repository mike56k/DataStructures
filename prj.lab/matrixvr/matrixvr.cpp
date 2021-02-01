// Copyright 2020 by Isachenko Mikhail under Free Public License 1.0.0

#include "matrixvr.h"
#include <stdexcept>

MatrixVr::MatrixVr()
{
  data_ = nullptr;
}

MatrixVr::MatrixVr(const MatrixVr& m) :
  n_col_(m.n_col_), n_row_(m.n_row_)
{
  data_ = new float[m.n_col_ * m.n_row_]{0.0f};
  for (int i = 0; i < n_row_; i++) {
    for (int j = 0; j < n_col_; j++) {
      at(i, j) = m.at(i, j);
    }
  }
}

MatrixVr::MatrixVr(const ptrdiff_t col_count, const ptrdiff_t  row_count)
{
  if (col_count <= 0 || row_count <= 0) {
    throw std::out_of_range("Col or Row count can't be less than 0");
  }
  n_col_ = col_count;
  n_row_ = row_count;
  data_ = new float[col_count * row_count]{0.0f};
}

MatrixVr::~MatrixVr()
{
    delete [] data_;
}

MatrixVr& MatrixVr::operator=(const MatrixVr& rhs) noexcept
{
  delete [] data_;
  data_ = new float[rhs.rowCount() * rhs.colCount()]{0.0f};
  n_row_ = rhs.rowCount();
  n_col_ = rhs.colCount();
  for (ptrdiff_t i = 0; i < rhs.rowCount(); i++) {
    for (ptrdiff_t j = 0; j < rhs.colCount(); j++) {
      at(i,j) = rhs.at(i,j);
    }
  }
  return *this;
}

float& MatrixVr::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) {
  if (row_i < 0 || n_row_ <= row_i) {
    throw std::out_of_range("MatrixVr::at - row index out of range");
  }
  if (col_i < 0 || n_col_ <= col_i) {
    throw std::out_of_range("MatrixVr::at - column index out of range");
  }
  const std::ptrdiff_t i = row_i * n_col_ + col_i;
  return data_[i];
}


float MatrixVr::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) const {
  if (row_i < 0 || n_row_ <= row_i) {
    throw std::out_of_range("MatrixVr::at const - row index out of range");
  }
  if (col_i < 0 || n_col_ <= col_i) {
    throw std::out_of_range("MatrixVr::at const - column index out of range");
  }
  const std::ptrdiff_t i = row_i * n_col_ + col_i;
  return data_[i];
}

MatrixVr& MatrixVr::transpose() noexcept
{
  MatrixVr temp(n_row_, n_col_);
  for (std::ptrdiff_t i = 0; i < n_row_; ++i) {
    for (std::ptrdiff_t j = 0; j < n_col_; ++j) {
      temp.at(j, i) = at(i, j);
    }
  }
  *this = temp;
  return *this;
}

MatrixVr& MatrixVr::multiply(const MatrixVr& rhs) noexcept(false)
{
  if (n_col_ != rhs.n_row_) throw std::invalid_argument("Number of cols is not equal to number of rows");
  MatrixVr temp(rhs.colCount(), rowCount());
  for (std::ptrdiff_t i = 0; i < rowCount(); i++) {
    for (std::ptrdiff_t j = 0; j < rhs.colCount(); j++) {
      temp.at(i, j) = 0;
      for (std::ptrdiff_t k = 0; k < rhs.rowCount(); k++) {
        temp.at(i, j) += at(i, k) * rhs.at(k, j);
      }
    }
  }
  *this = temp;
  return *this;
}

void MatrixVr::swapRows(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second)
{
  if (i_first<0 || i_first>n_row_ || i_second<0 || i_second>n_row_) {
    throw std::out_of_range("Index out of range");
  }
  if (i_second == i_first) {
    return;
  }
  float num{0};
  for (int i = 0; i < n_col_; i++) {
    num = at(i_first, i);
    at(i_first, i) = at(i_second, i);
    at(i_second, i) = num;
  }
}

void MatrixVr::swapColumns(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second)
{
  if (i_first<0 || i_first>=n_col_ || i_second<0 || i_second>=n_col_) {
    throw std::out_of_range("Index out of range");
  }
  float temp{0};
  for (int i = 0; i < n_row_; i++) {
    temp = at(i, i_first);
    at(i, i_first) = at(i, i_second);
    at(i, i_second) = temp;
  }
}

bool MatrixVr::operator==(const MatrixVr& rhs) const noexcept
{
  bool res = (rhs.n_col_ == n_col_ && rhs.n_row_ == n_row_);
  if (res) {
    for (int i = 0; i < n_row_; i++) {
      for (int j = 0; j < n_col_; j++) {
        if (rhs.at(i, j) != at(i, j)) {
          res = false;
          break;
        }
      }
    }
  }
  return res;
}
