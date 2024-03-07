def levenshtein(strx, stry, is_print=False):
    len_stry = len(stry)
    len_strx = len(strx)

    mtr = [[0 for _ in range(len_stry + 1)] for _ in range(len_strx + 1)]

    for i in range(1, len_strx + 1):
        mtr[i][0] = i
    for j in range(1, len_stry + 1):
        mtr[0][j] = j

    for i in range(1, len_strx + 1):
        for j in range(1, len_stry + 1):
            cost = 0 if strx[i - 1] == stry[j - 1] else 1
            mtr[i][j] = min(mtr[i - 1][j] + 1, mtr[i][j - 1] + 1, mtr[i - 1][j - 1] + cost)
    if (is_print):
        return mtr
    return mtr[len_strx][len_stry]


def damerauLevenshtein(strx, stry, is_print=False):
    len_stry = len(stry)
    len_strx = len(strx)
    mtr = [[0 for _ in range(len_stry + 1)] for _ in range(len_strx + 1)]

    for i in range(1, len_strx + 1):
        mtr[i][0] = i
    for j in range(1, len_stry + 1):
        mtr[0][j] = j

    for i in range(1, len_strx + 1):
        for j in range(1, len_stry + 1):
            cost = 0 if strx[i - 1] == stry[j - 1] else 1
            mtr[i][j] = min(mtr[i - 1][j] + 1, mtr[i][j - 1] + 1, mtr[i - 1][j - 1] + cost)
            if (i > 1 and j > 1 and strx[i - 1] == stry[j - 2] and strx[i - 2] == stry[j - 1]):
                mtr[i][j] = min(mtr[i][j], mtr[i - 2][j - 2] + 1)
    if is_print:
        return mtr
    return mtr[len_strx][len_stry]


def damerauLevenshteinRecurs(strx, stry, is_print=False):
    len_strx = len(strx)
    len_stry = len(stry)

    if len_strx == 0 or len_stry == 0:
        return max(len_strx, len_stry)

    cost_del_ins_rep = min(
        [damerauLevenshteinRecurs(strx[:-1], stry) + 1, damerauLevenshteinRecurs(strx, stry[:-1]) + 1,
         damerauLevenshteinRecurs(strx[: - 1], stry[: - 1]) + m(strx[-1], stry[-1])])

    if len_strx > 1 and len_stry > 1 and strx[-1] == stry[-2] and strx[-2] == stry[-1]:
        cost_del_ins_rep = min(cost_del_ins_rep, damerauLevenshteinRecurs(strx[:-2], stry[:-2]) + 1)

    return cost_del_ins_rep


def m(a, b):
    return 0 if a == b else 1


def dLRC(strx, stry, is_print=False):
    cache = [[-1] * (len(stry) + 1) for _ in range(len(strx) + 1)]
    min_len = max(len(strx), len(stry)) + 1

    def dlrc(strx, stry):
        len_strx = len(strx)
        len_stry = len(stry)

        if len_strx == 0 or len_stry == 0:
            cache[len_strx][len_stry] = max(len_strx, len_stry)
            return cache[len_strx][len_stry]

        if cache[len_strx - 1][len_stry] >= 0:
            del_cost = cache[len_strx - 1][len_stry]
        else:
            del_cost = dlrc(strx[:-1], stry)
            cache[len_strx - 1][len_stry] = del_cost

        if cache[len_strx][len_stry - 1] >= 0:
            ins_cost = cache[len_strx][len_stry - 1]
        else:
            ins_cost = dlrc(strx, stry[:-1])
            cache[len_strx][len_stry - 1] = ins_cost

        if cache[len_strx - 1][len_stry - 1] >= 0:
            rep_cost = cache[len_strx - 1][len_stry - 1]
        else:
            rep_cost = dlrc(strx[:-1], stry[:-1])
            cache[len_strx - 1][len_stry - 1] = rep_cost

        min_len = min([del_cost + 1,
                       ins_cost + 1,
                       rep_cost + m(strx[-1], stry[-1])])

        if len_strx > 1 and len_stry > 1 and strx[-1] == stry[-2] and strx[-2] == stry[-1]:
            if cache[len_strx - 2][len_stry - 2] >= 0:
                trnsps_cost = cache[len_strx - 1][len_stry - 1]
            else:
                trnsps_cost = dlrc(strx[:-2], stry[:-2])
                cache[len_strx - 2][len_stry - 2] = trnsps_cost
            min_len = min(min_len, trnsps_cost + 1)

        cache[len(strx)][len(stry)] = min_len
        return min_len

    return dlrc(strx, stry)
