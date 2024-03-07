#include "alg.h"

Matrix Multiply::classicAlg(const Matrix &mtrx, const Matrix &mtry) {
    size_t rows1 = mtrx.rows();
    size_t cols1 = mtrx.columns();
    size_t cols2 = mtry.columns();

    Matrix mtr_res(rows1, cols2, 0);

    for (size_t i = 0; i < rows1; ++i)
        for (size_t j = 0; j < cols2; ++j)
            for (size_t k = 0; k < cols1; ++k)
                mtr_res[i][j] += mtrx[i][k] * mtry[k][j];

    return mtr_res;
}

Matrix Multiply::winograd(const Matrix &mtrx, const Matrix &mtry) {
    size_t rows1 = mtrx.rows();
    size_t cols1 = mtrx.columns();
    size_t cols2 = mtry.columns();

    Matrix mtr_res(rows1, rows1);

    std::vector<int> rowFactors(rows1, 0);
    std::vector<int> colFactors(cols2, 0);

    for (size_t i = 0; i < rows1; ++i)
        for (size_t j = 0; j < cols1 / 2; ++j)
            rowFactors[i] += mtrx[i][2 * j] * mtrx[i][2 * j + 1];

    for (size_t i = 0; i < cols2; ++i)
        for (size_t j = 0; j < cols1 / 2; ++j)
            colFactors[i] += mtry[2 * j][i] * mtry[2 * j + 1][i];

    for (size_t i = 0; i < rows1; ++i) {
        for (size_t j = 0; j < cols2; ++j) {
            mtr_res[i][j] = -rowFactors[i] - colFactors[j];
            for (size_t k = 0; k < cols1 / 2; ++k) {
                mtr_res[i][j] += (mtrx[i][2 * k] + mtry[2 * k + 1][j]) *
                                 (mtrx[i][2 * k + 1] + mtry[2 * k][j]);
            }
        }
    }

    if (cols1 % 2) {
        for (size_t i = 0; i < rows1; ++i)
            for (size_t j = 0; j < cols2; ++j)
                mtr_res[i][j] += mtrx[i][cols1 - 1] * mtry[cols1 - 1][j];
    }

    return mtr_res;
}


Matrix Multiply::winogradOpt(const Matrix &mtrx, const Matrix &mtry) {
    size_t rows1 = mtrx.rows();
    size_t cols1 = mtrx.columns();
    size_t cols2 = mtry.columns();

    Matrix mtr_res(rows1, rows1);

    std::vector<int> rowFactors(rows1, 0);
    std::vector<int> colFactors(cols2, 0);

    size_t halfCols = cols1 >> 1;

    for (size_t i = 0; i < rows1; ++i) {
        for (size_t j = 0; j < halfCols; ++j) {
            size_t jMul = j << 1;
            rowFactors[i] += mtrx[i][jMul] * mtrx[i][jMul + 1];
        }
    }

    for (size_t i = 0; i < cols2; ++i) {
        for (size_t j = 0; j < halfCols; ++j) {
            size_t jMul = j << 1;
            colFactors[i] += mtry[jMul][i] * mtry[jMul + 1][i];
        }
    }

    for (size_t i = 0; i < rows1; ++i) {
        for (size_t j = 0; j < cols2; ++j) {
            mtr_res[i][j] = -rowFactors[i] - colFactors[j];
            for (size_t k = 0; k < halfCols; ++k) {
                size_t kMul = k << 1;
                mtr_res[i][j] += (mtrx[i][kMul] + mtry[kMul + 1][j]) *
                                 (mtrx[i][kMul + 1] + mtry[kMul][j]);
            }
        }
    }

    if (cols1 % 2) {
        for (size_t i = 0; i < rows1; ++i)
            for (size_t j = 0; j < cols2; ++j)
                mtr_res[i][j] += mtrx[i][cols1 - 1] * mtry[cols1 - 1][j];
    }

    return mtr_res;
}

Matrix Multiply::strassenAlg(const Matrix &mtrx, const Matrix &mtry) {
    size_t rows = mtrx.rows();

    if (rows <= 2) {
        return classicAlg(mtrx, mtry);
    }

    size_t n = mtrx.rows() / 2;

    auto a11 = mtrx.getSubMatrix(0, n, 0, n);
    auto a12 = mtrx.getSubMatrix(0, n, n, rows);
    auto a21 = mtrx.getSubMatrix(n, rows, 0, n);
    auto a22 = mtrx.getSubMatrix(n, rows, n, rows);

    auto b11 = mtry.getSubMatrix(0, n, 0, n);
    auto b12 = mtry.getSubMatrix(0, n, n, rows);
    auto b21 = mtry.getSubMatrix(n, rows, 0, n);
    auto b22 = mtry.getSubMatrix(n, rows, n, rows);

    auto p1 = strassenAlg(a11 + a22, b11 + b22);
    auto p2 = strassenAlg(a22, b21 - b11);
    auto p3 = strassenAlg(a11 + a12, b22);
    auto p4 = strassenAlg(a12 - a22, b21 + b22);
    auto p5 = strassenAlg(a11, b12 - b22);
    auto p6 = strassenAlg(a21 + a22, b11);
    auto p7 = strassenAlg(a11 - a21, b11 + b12);

    auto c11 = p1 + p2 - p3 + p4;
    auto c12 = p5 + p3;
    auto c21 = p6 + p2;
    auto c22 = p5 + p1 - p6 - p7;

    return Matrix::combineMatrices(c11, c12, c21, c22);
}

