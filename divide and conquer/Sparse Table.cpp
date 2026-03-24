# Sparse Table for RMQ

import math

def build_sparse(arr):
    n = len(arr)
    k = int(math.log2(n)) + 1
    st = [[0]*n for _ in range(k)]

    for i in range(n):
        st[0][i] = arr[i]

    j = 1
    while (1 << j) <= n:
        for i in range(n - (1 << j) + 1):
            st[j][i] = min(st[j-1][i],
                           st[j-1][i + (1 << (j-1))])
        j += 1

    return st


def query(st, L, R):
    j = int(math.log2(R - L + 1))
    return min(st[j][L], st[j][R - (1 << j) + 1])


arr = [1, 3, 2, 7, 9, 11]
st = build_sparse(arr)
print("Minimum in range(1,4):", query(st, 1, 4))