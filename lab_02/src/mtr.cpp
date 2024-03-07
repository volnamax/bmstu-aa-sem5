#include "mtr.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

Matrix::Matrix(int rows, int cols)
        : m_Data(rows, std::vector<int>(cols)) {
    std::srand(std::time(nullptr));
}

Matrix::Matrix(int rows, int cols, int val)
        : Matrix(rows, cols) {
    for (auto &row: m_Data)
        std::fill(row.begin(), row.end(), val);
}

Matrix Matrix::slice(size_t row_start, size_t row_end, size_t col_start, size_t col_end) const {
    Matrix res(row_end - row_start, col_end - col_start);
    for (size_t i = row_start; i < row_end; ++i)
        for (size_t j = col_start; j < col_end; ++j)
            res[i - row_start][j - col_start] = m_Data[i][j];
    return res;
}

Matrix Matrix::getSubMatrix(size_t rowStart, size_t rowEnd, size_t colStart, size_t colEnd) const {
    Matrix result(rowEnd - rowStart, colEnd - colStart);
    for (size_t i = rowStart; i < rowEnd; ++i)
        for (size_t j = colStart; j < colEnd; ++j)
            result[i - rowStart][j - colStart] = m_Data[i][j];
    return result;
}

Matrix Matrix::combineMatrices(const Matrix &topLeft, const Matrix &topRight, const Matrix &bottomLeft,
                               const Matrix &bottomRight) {
    size_t n = topLeft.rows();
    size_t rows = n * 2;

    Matrix result(rows, rows);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            result.m_Data[i][j] = topLeft[i][j];
            result.m_Data[i][j + n] = topRight[i][j];
            result.m_Data[i + n][j] = bottomLeft[i][j];
            result.m_Data[i + n][j + n] = bottomRight[i][j];
        }
    }
    return result;
}

void Matrix::fillRandom(int maxVal) {
    for (size_t i = 0; i < m_Data.size(); ++i)
        for (size_t j = 0; j < m_Data[0].size(); ++j)
            m_Data[i][j] = std::rand() % maxVal;
}

Matrix Matrix::fromFile(const std::string &filename) {
    std::ifstream file{filename};
    if (!file.is_open()) {
        std::stringstream errStream;
        errStream << "Error opening file \"" << filename << "\"\n";
        throw std::runtime_error(errStream.str());
    }

    Matrix matrix;
    std::string line;
    while (getline(file, line)) {
        if (line.empty())
            continue;
        int value;
        std::vector<int> row;
        std::stringstream curRow(line);
        while (curRow >> value) {
            row.emplace_back(value);
        }
        matrix.m_Data.emplace_back(std::move(row));
    }

    if (matrix.m_Data.empty()) {
        throw std::runtime_error("No valid matrix data found in the file.");
    }

    return matrix;
}

Matrix Matrix::operator+(const Matrix &other) const {
    size_t rows = m_Data.size();
    size_t cols = m_Data[0].size();
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            result[i][j] = m_Data[i][j] + other.m_Data[i][j];
    return result;
}

Matrix Matrix::operator-(const Matrix &other) const {
    size_t rows = m_Data.size();
    size_t cols = m_Data[0].size();
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            result[i][j] = m_Data[i][j] - other.m_Data[i][j];
    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    for (const auto &row : matrix.m_Data) {
        os << "| ";
        for (const auto &value : row)
            os << std::setw(5) << value << " ";
        os << "|\n";
    }
    return os;
}
