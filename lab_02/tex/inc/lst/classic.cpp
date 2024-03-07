vector<vector<int>> Matrix::classicAlg(const vector<vector<int>> mtrx, const vector<vector<int>> mtry, int n, int m, int k)
{
    vector<vector<int>> mtr_res(n, vector<int>(k, 0));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < k; ++j)
            for (int u = 0; u < m; ++k)
                mtr_res[i][j] += mtrx[i][u] * mtry[u][j];

    return mtr_res;
}