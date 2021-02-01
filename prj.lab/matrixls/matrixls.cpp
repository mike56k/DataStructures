#include "matrixls.h"

MatrixLs::MatrixLs(const std::ptrdiff_t col_count, const std::ptrdiff_t row_count) : n_col_(col_count), n_row_(row_count)
{
  if (row_count <= 0 || col_count <= 0) throw std::out_of_range("Col count or row count is lest than zero");
  std::vector<ptrdiff_t> rows(row_count,0);
  std::vector<ptrdiff_t> cols(col_count,0);

  ptrdiff_t c = 0;
  for (ptrdiff_t i = 0; i < row_count; i++) {
    rows[i] = c;
    c += col_count;
  }
  for (ptrdiff_t i = 0; i < col_count; i++) {
    cols[i] = i;
  }
  std::vector<float> data(row_count * col_count,0);
    
  data_ = data;
  rows_ = rows;
  cols_ = cols;
}

float& MatrixLs::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) {
  if (row_i < 0 || n_row_ <= row_i) {
    throw std::out_of_range("MatrixVs::at - row index out of range");
  }
  if (col_i < 0 || n_col_ <= col_i) {
    throw std::out_of_range("MatrixVs::at - column index out of range");
  }
  return data_[rows_[row_i]+cols_[col_i]];
}

float MatrixLs::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) const {
  if (row_i < 0 || n_row_ <= row_i) {
    throw std::out_of_range("MatrixVs::at const - row index out of range");
  }
  if (col_i < 0 || n_col_ <= col_i) {
    throw std::out_of_range("MatrixVs::at const - column index out of range");
  }
  return data_[rows_[row_i] + cols_[col_i]];
}

MatrixLs& MatrixLs::transpose() noexcept
{
  MatrixLs temp(n_row_, n_col_);
  for (std::ptrdiff_t i = 0; i < n_row_; ++i) {
    for (std::ptrdiff_t j = 0; j < n_col_; ++j) {
      temp.at(j, i) = at(i, j);
    }
  }
  *this = temp;
  return *this;
}

MatrixLs& MatrixLs::multiply(const MatrixLs& rhs) noexcept(false)
{
  if (n_col_ != rhs.rowCount()) throw std::invalid_argument("Number of cols is not equal to number of rows");
  MatrixLs temp(rhs.colCount(), rowCount());
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

void MatrixLs::swapRows(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second)
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

void MatrixLs::swapColumns(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second)
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

bool MatrixLs::operator==(const MatrixLs& rhs) const noexcept
{
  return (data_ == rhs.data_ && n_col_ == rhs.n_col_ && n_row_ == rhs.n_row_);
}
