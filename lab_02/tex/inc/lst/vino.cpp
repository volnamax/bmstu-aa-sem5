vector<vector<int>> Matrix::winogradAlg(const vector<vector<int>> mtrx, const vector<vector<int>> mtry, int n, int m, int k)
{
    vector<vector<int>> mtr_res(n, vector<int>(k, 0));

    vector<int> row(n, 0);
    vector<int> col(k, 0);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m / 2; ++j)
            row[i] = row[i] + mtrx[i][2 * j] * mtrx[i][2 * j + 1];

    for (int i = 0; i < k; ++i)
        for (int j = 0; j < m / 2; ++j)
            col[i] = col[i] + mtry[2 * j][i] * mtry[2 * j + 1][i];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < k; ++j)
        {
            mtr_res[i][j] = -row[i] - col[j];
            for (int u = 0; u < m / 2; ++u)
                mtr_res[i][j] = mtr_res[i][j] + (mtrx[i][2 * u] + mtry[2 * u + 1][j]) * (mtrx[i][2 * u + 1] + mtry[2 * u][j]);
        }

    if (m % 2 == 1)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < k; ++j)
                mtr_res[i][j] = mtr_res[i][j] + mtrx[i][m - 1] * mtry[m - 1][j];
    return mtr_res;
