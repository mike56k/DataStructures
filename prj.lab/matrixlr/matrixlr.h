// Copyright 2020 by Polevoy Dmitry under Free Public License 1.0.0

#pragma once
#ifndef MATRIXLR_MATRIXLR_H_20201020
#define MATRIXLR_MATRIXLR_H_20201020

#include <iosfwd>
#include <vector>
#include <stdexcept>
class MatrixLr {
public:
  MatrixLr();
  MatrixLr(const MatrixLr&) noexcept;
  MatrixLr(const std::ptrdiff_t col_count, const std::ptrdiff_t row_count);
  ~MatrixLr();
  MatrixLr& operator=(const MatrixLr&) noexcept;

  std::ptrdiff_t rowCount() const noexcept { return n_row_; }
  std::ptrdiff_t colCount() const noexcept { return n_col_; }
  float& at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) noexcept(false);
  float at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) const noexcept(false);
  MatrixLr& transpose() noexcept;
  MatrixLr& multiply(const MatrixLr& rhs) noexcept(false);
  void swapRows(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second);
  void swapColumns(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second);
  bool MatrixLr::operator==(const MatrixLr& rhs) const noexcept;

private:
  std::ptrdiff_t n_row_{ 0 };
  std::ptrdiff_t n_col_{ 0 };
  std::ptrdiff_t* rows_;
  std::ptrdiff_t* cols_;
  float* data_;

};

#endif