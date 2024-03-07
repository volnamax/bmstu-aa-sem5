vector<vector<int>> Matrix::strassen(vector<vector<int>> mtrx, vector<vector<int>> mtry)
{
    size_t rows = mtrx.rows();

    if (rows <= 2)
        return classicAlg(mtrx, mtry);

    size_t half_row = mtrx.rows() / 2;

    auto a11 = mtrx.slice(0, half_row, 0, half_row);
    auto a12 = mtrx.slice(0, half_row, half_row, rows);
    auto a21 = mtrx.slice(half_row, rows, 0, half_row);
    auto a22 = mtrx.slice(half_row, rows, half_row, rows);

    auto b11 = mtry.slice(0, half_row, 0, half_row);
    auto b12 = mtry.slice(0, half_row, half_row, rows);
    auto b21 = mtry.slice(half_row, rows, 0, half_row);
    auto b22 = mtry.slice(half_row, rows, half_row, rows);

    auto p1 = strassen(a11 + a22, b11 + b22);
    auto p2 = strassen(a22, b21 - b11);
    auto p3 = strassen(a11 + a12, b22);
    auto p4 = strassen(a12 - a22, b21 + b22);
    auto p5 = strassen(a11, b12 - b22);
    auto p6 = strassen(a21 + a22, b11);
    auto p7 = strassen(a11 - a21, b11 + b12);

    auto c11 = p1 + p2 - p3 + p4;
    auto c12 = p5 + p3;
    auto c21 = p6 + p2;
    auto c22 = p5 + p1 - p6 - p7;

    return combine(c11, c12, c21, c22);
}