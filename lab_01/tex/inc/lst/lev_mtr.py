def levenshtein(X, Y):
	m = len(X)	
 	n = len(Y)

	mtr = [[0 for _ in range(n + 1)] for _ in range(m + 1)]
	
	for i in range(1, m + 1):
	    mtr[i][0] = i
	for j in range(1, n + 1):
	    mtr[0][j] = j
	
	for i in range(1, m + 1):
        for j in range(1, n + 1):
            cost = 0 if X[i - 1] == Y[j - 1] else 1
            mtr[i][j] = min(mtr[i - 1][j] + 1,
                            mtr[i][j - 1] + 1, 
                            mtr[i - 1][j - 1] + cost)
	
	return mtr[m][n]