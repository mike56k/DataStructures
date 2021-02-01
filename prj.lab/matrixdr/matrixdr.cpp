// Copyright 2020 by Isachenko Mikhail under Free Public License 1.0.0

#include "matrixdr.h"
#include <stdexcept>

MatrixDr::MatrixDr()
{
  data_ = new float*[0];
}

MatrixDr::MatrixDr(const MatrixDr& m) :
  n_col_(m.colCount()), n_row_(m.rowCount())
{
  data_ = new float*[n_row_];
  if (n_row_ == 0) data_ = nullptr;

  for (ptrdiff_t i = 0; i < m.rowCount(); i++) {
    data_[i] = new float[n_col_];
    for (ptrdiff_t j = 0; j < m.colCount(); j++) {
      at(i,j) = m.at(i,j);
    }
  }
}

MatrixDr::MatrixDr(const ptrdiff_t col_count, const ptrdiff_t  row_count) : n_col_(col_count), n_row_(row_count)
{
  if (col_count <= 0 || row_count <= 0) {
    throw std::invalid_argument("Col or Row count can't be less than 0");
  }


  data_ = new float*[row_count];
  for (ptrdiff_t i = 0; i < row_count; i++) {
    data_[i] = new float[col_count]{0.0f};
  }

}

MatrixDr::~MatrixDr()
{
  if (data_) {
    for (ptrdiff_t i = 0; i < n_row_; i++) {
      delete[] data_[i];
    }
    delete[] data_;
  }

}

MatrixDr& MatrixDr::operator=(const MatrixDr& rhs) noexcept
{
  if (*this == rhs) return *this;
  for (ptrdiff_t i = 0; i < n_row_; i++) {
    delete[] data_[i];
  }
  delete[] data_;

  n_row_ = rhs.rowCount();
  n_col_ = rhs.colCount();
  data_ = new float* [n_row_];
  if (n_row_ == 0) data_ = nullptr;

  for (ptrdiff_t i = 0; i < n_row_; i++) {
    data_[i] = new float[n_col_]{0};
    for (ptrdiff_t j = 0; j < n_col_; j++) {
      data_[i][j] = rhs.at(i, j);
    }
  }
  return *this;
}

float& MatrixDr::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) {
  if (row_i < 0 || n_row_ <= row_i) {
    throw std::out_of_range("MatrixDr::at - row index out of range");
  }
  if (col_i < 0 || n_col_ <= col_i) {
    throw std::out_of_range("MatrixDr::at - column index out of range");
  }
  return data_[row_i][col_i];
}


float MatrixDr::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) const {
  if (row_i < 0 || n_row_ <= row_i) {
    throw std::out_of_range("MatrixDr::at const - row index out of range");
  }
  if (col_i < 0 || n_col_ <= col_i) {
    throw std::out_of_range("MatrixDr::at const - column index out of range");
  }
  return data_[row_i][col_i];
}

MatrixDr& MatrixDr::transpose() noexcept
{
  MatrixDr temp(n_row_, n_col_);
  for (std::ptrdiff_t i = 0; i < n_row_; ++i) {
    for (std::ptrdiff_t j = 0; j < n_col_; ++j) {
      temp.at(j, i) = at(i, j);
    }
  }
  *this = temp;
  return *this;
}

MatrixDr& MatrixDr::multiply(const MatrixDr& rhs) noexcept(false)
{
  if (n_col_ != rhs.n_row_) throw std::invalid_argument("Number of cols is not equal to number of rows");
  MatrixDr temp(rhs.colCount(), rowCount());
  for (ptrdiff_t i = 0; i < rowCount(); i++) {
    for (ptrdiff_t j = 0; j < rhs.colCount(); j++) {
      temp.at(i, j) = 0;
      for (ptrdiff_t k = 0; k < rhs.rowCount(); k++) {
        temp.at(i, j) += at(i, k) * rhs.at(k, j);
      }
    }
  }
  *this = temp;
  return *this;
}

void MatrixDr::swapRows(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second)
{
  if (i_first<0 || i_first>=n_row_ || i_second<0 || i_second>=n_row_) {
    throw std::out_of_range("Index out of range");
  }
  float num;
  for (int i = 0; i < n_col_; i++) {
    num = at(i_first, i);
    at(i_first, i) = at(i_second, i);
    at(i_second, i) = num;
  }
}

void MatrixDr::swapColumns(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second)
{
  if (i_first<0 || i_first>=n_col_ || i_second<0 || i_second>=n_col_) {
    throw std::out_of_range("Index out of range");
  }
  if(i_first == i_second) return;
  float temp;
  for (int i = 0; i < n_row_; i++) {
    temp = at(i, i_first);
    at(i, i_first) = at(i, i_second);
    at(i, i_second) = temp;
  }
}

bool MatrixDr::operator==(const MatrixDr& rhs) const noexcept
{
  if (colCount() != rhs.colCount() || rowCount() != rhs.rowCount()) return false;
  for (ptrdiff_t i = 0; i < rowCount(); i++) {
    for (ptrdiff_t j = 0; j < colCount(); j++) {
      if (at(i, j) != rhs.at(i, j)) {
        return false;
      }
    }
  }
  return true;
}
