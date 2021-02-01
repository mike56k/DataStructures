#include "matrixlr.h"

MatrixLr::MatrixLr()
{
  data_ = nullptr;
  rows_ = new ptrdiff_t[0];
  cols_ = new ptrdiff_t[0];
  
}

MatrixLr::MatrixLr(const MatrixLr& rhs) noexcept
  : n_row_(rhs.n_row_), n_col_(rhs.n_col_), data_(new float[rhs.n_col_ * rhs.n_row_])
  , rows_(new std::ptrdiff_t[rhs.n_row_]), cols_(new std::ptrdiff_t[rhs.n_col_]) {
  std::copy(rhs.data_, rhs.data_ + n_col_ * n_row_, data_);
  std::copy(rhs.rows_, rhs.rows_ + n_row_, rows_);
  std::copy(rhs.cols_, rhs.cols_ + n_col_, cols_);
}

MatrixLr::MatrixLr(const std::ptrdiff_t col_count, const std::ptrdiff_t row_count) : n_col_(col_count), n_row_(row_count)
{
  if (row_count <= 0 || col_count <= 0) throw std::out_of_range("Col count or row count is lest than zero");
  data_ = new float[row_count * col_count];
  rows_ = new ptrdiff_t[row_count];
  cols_ = new ptrdiff_t[col_count];
  ptrdiff_t c = 0;
  for (ptrdiff_t i = 0; i < row_count; i++) {
    rows_[i] = c;
    c += col_count;
  }
  for (ptrdiff_t i = 0; i < col_count; i++) {
    cols_[i] = i;
  }
  for (ptrdiff_t i = 0; i < rowCount(); i++) {
    for (ptrdiff_t j = 0; j < colCount(); j++) {
      at(i, j) = 0;
    }
  }
}

MatrixLr::~MatrixLr()
{
  delete [] data_;
  delete [] cols_;
  delete [] rows_;
}

MatrixLr& MatrixLr::operator=(const MatrixLr& rhs) noexcept {
  if (*this == rhs) return *this;
  delete[] data_;
  delete[] rows_;
  delete[] cols_;
  n_row_ = rhs.n_row_;
  n_col_ = rhs.n_col_;
  data_ = new float[n_col_ * n_row_];
  rows_ = new std::ptrdiff_t[n_row_];
  cols_ = new std::ptrdiff_t[n_col_];
  std::copy(rhs.data_, rhs.data_ + n_col_ * n_row_, data_);
  std::copy(rhs.rows_, rhs.rows_ + n_row_, rows_);
  std::copy(rhs.cols_, rhs.cols_ + n_col_, cols_);
  return *this;
}

float& MatrixLr::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) {
  if (row_i < 0 || n_row_ <= row_i) {
    throw std::out_of_range("MatrixVs::at - row index out of range");
  }
  if (col_i < 0 || n_col_ <= col_i) {
    throw std::out_of_range("MatrixVs::at - column index out of range");
  }
  return data_[rows_[row_i] + cols_[col_i]];
}

float MatrixLr::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) const {
  if (row_i < 0 || n_row_ <= row_i) {
    throw std::out_of_range("MatrixVs::at const - row index out of range");
  }
  if (col_i < 0 || n_col_ <= col_i) {
    throw std::out_of_range("MatrixVs::at const - column index out of range");
  }
  return data_[rows_[row_i] + cols_[col_i]];
}

MatrixLr& MatrixLr::transpose() noexcept
{
  MatrixLr temp(n_row_, n_col_);
  for (std::ptrdiff_t i = 0; i < n_row_; ++i) {
    for (std::ptrdiff_t j = 0; j < n_col_; ++j) {
      temp.at(j, i) = at(i, j);
    }
  }
  *this = temp;
  return *this;
}

MatrixLr& MatrixLr::multiply(const MatrixLr& rhs) noexcept(false)
{
  if (n_col_ != rhs.rowCount()) throw std::invalid_argument("Number of cols is not equal to number of rows");
  MatrixLr temp(rhs.colCount(), rowCount());
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

void MatrixLr::swapRows(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second)
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

void MatrixLr::swapColumns(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second)
{
  if (i_first<0 || i_first>=n_col_ || i_second<0 || i_second>=n_col_) {
    throw std::out_of_range("Index out of range");
  }
  float temp;
  for (int i = 0; i < n_row_; i++) {
    temp = at(i, i_first);
    at(i, i_first) = at(i, i_second);
    at(i, i_second) = temp;
  }
}

bool MatrixLr::operator==(const MatrixLr& rhs) const noexcept
{
  if (n_col_ != rhs.n_col_ || n_row_ != rhs.n_row_) {
    return false;
  }
  for (ptrdiff_t i = 0; i < rhs.rowCount(); i++) {
    for (ptrdiff_t j = 0; j < rhs.colCount(); j++) {
      if (at(i, j) != rhs.at(i, j)) {
        return false;
      }
    }
  }
  return true;
}
