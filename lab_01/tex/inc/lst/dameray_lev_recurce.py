def damerauLevenshteinRecurs(X, Y):
    m = len(X)
    n = len(Y)

    if m == 0 or n == 0:
     return max(m, n)

    cost_del_ins_rep = min(
    [damerauLevenshteinRecurs(X[:-1], Y) + 1, damerauLevenshteinRecurs(X, Y[:-1]) + 1,
    damerauLevenshteinRecurs(X[: - 1], Y[: - 1]) + m(X[-1], Y[-1])])

    if m > 1 and n > 1 and X[-1] == Y[-2] and X[-2] == Y[-1]:
        cost_del_ins_rep = min(cost_del_ins_rep, damerauLevenshteinRecurs(X[:-2], Y[:-2]) + 1)

    return cost_del_ins_rep

def m(a, b):
    return 0 if a == b else 1