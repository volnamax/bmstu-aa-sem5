#pragma once

#include <cstddef>
#include <vector>
#include <string>

class Matrix
{
public:
    Matrix() = default;
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, int val);

    size_t rows() const { return m_Data.size(); }
    size_t columns() const { return m_Data[0].size(); }
    size_t size() const { return m_Data.size(); }

    Matrix getSubMatrix(size_t rowStart, size_t rowEnd, size_t colStart, size_t colEnd) const;

    static Matrix combineMatrices(const Matrix &topLeft, const Matrix &topRight, const Matrix &bottomLeft, const Matrix &bottomRight);
    Matrix readFromFile(const std::string &filename);

    Matrix slice(size_t row_start, size_t row_end, size_t col_start, size_t col_end) const;
    static Matrix combine(const Matrix &a11, const Matrix &a12, const Matrix &a21, const Matrix &a22);

    void fillRandom(int maxVal = 1000);

    static Matrix fromFile(const std::string &filename);

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
    std::vector<int> &operator[](int i) { return m_Data[i]; }
    const std::vector<int> &operator[](int i) const { return m_Data[i]; }

    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;

private:
    std::vector<std::vector<int>> m_Data;
};