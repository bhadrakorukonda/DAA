def solve_n_queens(n):
    board = [["."] * n for _ in range(n)]
    res = []

    def is_safe(r, c):
        for i in range(r):
            if board[i][c] == "Q":
                return False
        i, j = r-1, c-1
        while i >= 0 and j >= 0:
            if board[i][j] == "Q":
                return False
            i -= 1; j -= 1
        i, j = r-1, c+1
        while i >= 0 and j < n:
            if board[i][j] == "Q":
                return False
            i -= 1; j += 1
        return True

    def backtrack(r):
        if r == n:
            res.append(["".join(row) for row in board])
            return
        for c in range(n):
            if is_safe(r, c):
                board[r][c] = "Q"
                backtrack(r+1)
                board[r][c] = "."

    backtrack(0)
    return res


# Example
print(solve_n_queens(4))