#ifndef MATRIXVS_H
#define MATRIXVS_H

#include <iosfwd>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

class MatrixVs {
public:
	MatrixVs() = default;
	MatrixVs(const std::ptrdiff_t col_count, const std::ptrdiff_t row_count) noexcept(false);
	MatrixVs(const MatrixVs&) = default;
	~MatrixVs() = default;
	MatrixVs& operator=(const MatrixVs& rhs) = default;
	MatrixVs& multiply(const MatrixVs& rhs) noexcept(false);
	size_t rowCount() const noexcept { return n_row_; }
	size_t colCount() const noexcept { return n_col_; }
	float& at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) noexcept(false);
	float at(const std::ptrdiff_t i_row, const std::ptrdiff_t i_col) const noexcept(false);
	MatrixVs& transpose() noexcept;
	void swapRows(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second) noexcept(false);
	void swapColumns(const std::ptrdiff_t i_first, const std::ptrdiff_t i_second) noexcept(false);
	bool operator==(const MatrixVs& rhs) const noexcept;
private:
	std::ptrdiff_t n_row_{ 0 };
	std::ptrdiff_t n_col_{ 0 };
	std::vector<float> data_;

};

#endif

