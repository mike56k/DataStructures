#include "matrixds.h"
#include <stdexcept>

MatrixDs::MatrixDs(const std::ptrdiff_t col_count, const std::ptrdiff_t row_count) noexcept(false) : n_col_(col_count), n_row_(row_count){
  if (row_count <= 0 || col_count <= 0) {
    throw std::out_of_range("Index out of range");
  }
  data_.resize(row_count, std::vector<float>(col_count));
}


float& MatrixDs::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) {
  if (row_i < 0 || n_row_ <= row_i) {
    throw std::out_of_range("MatrixDs::at - row index out of range");
  }
  if (col_i < 0 || n_col_ <= col_i) {
    throw std::out_of_range("MatrixDs::at - column index out of range");
  }
  return data_[row_i][col_i];
}


float MatrixDs::at(const std::ptrdiff_t row_i, const std::ptrdiff_t col_i) const {
  if (row_i < 0 || n_row_ <= row_i) {
    throw std::out_of_range("MatrixDs::at const - row index out of range");
  }
  if (col_i < 0 || n_col_ <= col_i) {
    throw std::out_of_range("MatrixDs::at const - column index out of range");
  }
  return data_[row_i][col_i];
}

bool MatrixDs::operator==(const MatrixDs& rhs) const noexcept {
  return (data_ == rhs.data_ && colCount() == rhs.colCount() && rowCount() == rhs.rowCount());
}

MatrixDs& MatrixDs::multiply(const MatrixDs& rhs) noexcept(false) {
  if (n_col_ != rhs.rowCount()) throw std::invalid_argument("Number of cols is not equal to number of rows");
  MatrixDs temp(rhs.colCount(), rowCount());
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

MatrixDs& MatrixDs::transpose() noexcept {
  MatrixDs temp(n_row_, n_col_);
  for (std::ptrdiff_t i = 0; i < n_row_; ++i) {
    for (std::ptrdiff_t j = 0; j < n_col_; ++j) {
      temp.at(j, i) = at(i, j);
    }
  }
  *this = temp;
  return *this;
}

void MatrixDs::swapRows(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second) noexcept(false) {
  if (i_first<0 || i_first >= n_row_ || i_second < 0 || i_second >= n_row_) {
    throw std::out_of_range("Index out of range");
  }
  float num;
  for (int i = 0; i < n_col_; i++) {
    num = at(i_first, i);
    at(i_first, i) = at(i_second, i);
    at(i_second, i) = num;
  }
}

void MatrixDs::swapColumns(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second) noexcept(false) {
  if (i_first < 0 || i_first >= n_col_ || i_second < 0 || i_second >= n_col_) {
    throw std::out_of_range("Index out of range");
  }
  float temp;
  for (int i = 0; i < n_row_; i++) {
    temp = at(i, i_first);
    at(i, i_first) = at(i, i_second);
    at(i, i_second) = temp;
  }
}