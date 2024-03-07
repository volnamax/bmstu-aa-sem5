vector<vector<int>> Matrix::winogradAlg(const vector<vector<int>> mtrx, const vector<vector<int>> mtry, int n, int m, int k)
{
    vector<vector<int>> mtr_res(n, vector<int>(k, 0));

    vector<int> row(n, 0);
    vector<int> col(k, 0);

    int half_m = m >> 1;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < half_m; ++j)
            row[i] += mtrx[i][j << 1] * mtrx[i][(j << 1) + 1];

    for (int i = 0; i < k; ++i)
        for (int j = 0; j < half_m; ++j)
            col[i] += mtry[j << 1][i] * mtry[(j << 1) + 1][i];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < k; ++j)
        {
            mtr_res[i][j] = -row[i] - col[j];
            for (int u = 0; u < half_m; ++u)
                mtr_res[i][j] += (mtrx[i][u << 1] + mtry[(u << 1) + 1][j]) * (mtrx[i][(u << 1) + 1] + mtry[u << 1][j]);
        }

    if (m % 2 == 1)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < k; ++j)
                mtr_res[i][j] += mtrx[i][m - 1] * mtry[m - 1][j];
    return mtr_res;
