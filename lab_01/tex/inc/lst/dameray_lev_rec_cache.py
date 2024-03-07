def dLRC(X, Y):
    cache = [[-1] * (len(Y) + 1) for _ in range(len(X) + 1)]
    min_len = max(len(X), len(Y)) + 1
    def dlrc(X, Y):
        len_X = len(X)
        len_Y = len(Y)
        if len_X == 0 or len_Y == 0:
            cache[len_X][len_Y] = max(len_X, len_Y)
            return cache[len_X][len_Y]
        if cache[len_X - 1][len_Y] >= 0:
            del_cost = cache[len_X - 1][len_Y]
        else:
            del_cost = dlrc(X[:-1], Y)
            cache[len_X - 1][len_Y] = del_cost
        if cache[len_X][len_Y - 1] >= 0:
            ins_cost = cache[len_X][len_Y - 1]
        else:
            ins_cost = dlrc(X, Y[:-1])
            cache[len_X][len_Y - 1] = ins_cost
        if cache[len_X - 1][len_Y - 1] >= 0:
            rep_cost = cache[len_X - 1][len_Y - 1]
        else:
            rep_cost = dlrc(X[:-1], Y[:-1])
            cache[len_X - 1][len_Y - 1] = rep_cost
        min_len = min([del_cost + 1,
                       ins_cost + 1,
                       rep_cost + m(X[-1], Y[-1])])
        if len_X > 1 and len_Y > 1 and X[-1] == Y[-2] and X[-2] == Y[-1]:
            if cache[len_X - 2][len_Y - 2] >= 0:
                trnsps_cost = cache[len_X - 1][len_Y - 1]
            else:
                trnsps_cost = dlrc(X[:-2], Y[:-2])
                cache[len_X - 2][len_Y - 2] = trnsps_cost
            min_len = min(min_len, trnsps_cost + 1)
        cache[len(X)][len(Y)] = min_len
        return min_len
    return dlrc(X, Y)