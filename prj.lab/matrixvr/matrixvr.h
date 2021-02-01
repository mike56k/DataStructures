// Copyright 2020 by Isachenko Mikhail under Free Public License 1.0.0

#pragma once
#ifndef MatrixVr_MATRIXVR_H_20201020
#define MatrixVr_MATRIXVR_H_20201020

#include <iosfwd>

class MatrixVr {
public:
  MatrixVr();
  MatrixVr(const MatrixVr&);
  MatrixVr(const std::ptrdiff_t col_count, const std::ptrdiff_t row_count);
  ~MatrixVr();
  MatrixVr& operator=(const MatrixVr&) noexcept;

  std::ptrdiff_t rowCount() const noexcept { return n_row_; }
  std::ptrdiff_t colCount() const noexcept { return n_col_; }
  float& at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) noexcept(false);
  float at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) const noexcept(false);
  MatrixVr& transpose() noexcept;
  MatrixVr& multiply(const MatrixVr& rhs) noexcept(false);
  void swapRows(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second);
  void swapColumns(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second);
  bool operator==(const MatrixVr& rhs) const noexcept;
private:
  std::ptrdiff_t n_row_{ 0 };
  std::ptrdiff_t n_col_{ 0 };
  float* data_;
};

#endif