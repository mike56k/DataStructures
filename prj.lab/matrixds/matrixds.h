// Copyright 2020 by Isachenko Mikhail under Free Public License 1.0.0

#pragma once
#ifndef MatrixDs_MatrixDs_H_20201020
#define MatrixDs_MatrixDs_H_20201020

#include <iosfwd>
#include <vector>

class MatrixDs {
public:
  MatrixDs() = default;
  MatrixDs(const MatrixDs&) = default;
  MatrixDs(const std::ptrdiff_t col_count, const std::ptrdiff_t row_count);
  ~MatrixDs() = default;
  MatrixDs& operator=(const MatrixDs&) = default;

  std::ptrdiff_t rowCount() const noexcept { return n_row_; }
  std::ptrdiff_t colCount() const noexcept { return n_col_; }
  float& at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) noexcept(false);
  float at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) const noexcept(false);
  MatrixDs& transpose() noexcept;
  MatrixDs& multiply(const MatrixDs &rhs);
  void swapRows(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second);
  void swapColumns(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second);
  bool MatrixDs::operator==(const MatrixDs& rhs) const noexcept;
private:
  std::ptrdiff_t n_row_{ 0 };
  std::ptrdiff_t n_col_{ 0 };
  std::vector<std::vector<float>> data_;
};

#endif