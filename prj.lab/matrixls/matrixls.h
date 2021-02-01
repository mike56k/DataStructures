// Copyright 2020 by Polevoy Dmitry under Free Public License 1.0.0

#pragma once
#ifndef MATRIXLS_MATRIXLS_H_20201020
#define MATRIXLS_MATRIXLS_H_20201020

#include <iosfwd>
#include <vector>
#include <stdexcept>
class MatrixLs {
public:
  MatrixLs() = default;
  MatrixLs(const MatrixLs&) = default;
  MatrixLs(const std::ptrdiff_t col_count, const std::ptrdiff_t row_count);
  ~MatrixLs() = default;
  MatrixLs& operator=(const MatrixLs&) = default;

  std::ptrdiff_t rowCount() const noexcept { return n_row_; }
  std::ptrdiff_t colCount() const noexcept { return n_col_; }
  float& at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) noexcept(false);
  float at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) const noexcept(false);
  MatrixLs& transpose() noexcept;
  MatrixLs& multiply(const MatrixLs& rhs) noexcept(false);
  void swapRows(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second);
  void swapColumns(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second);
  bool MatrixLs::operator==(const MatrixLs& rhs) const noexcept;

private:
  std::ptrdiff_t n_row_{ 0 };
  std::ptrdiff_t n_col_{ 0 };
  std::vector<std::ptrdiff_t> rows_;
  std::vector<std::ptrdiff_t> cols_;
  std::vector<float> data_;

};

#endif