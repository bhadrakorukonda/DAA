class FenwickTree:
    def __init__(self, n):
        self.n = n
        self.bit = [0] * (n + 1)

    def update(self, idx, delta):
        idx += 1
        while idx <= self.n:
            self.bit[idx] += delta
            idx += idx & -idx

    def query(self, idx):
        idx += 1
        result = 0
        while idx > 0:
            result += self.bit[idx]
            idx -= idx & -idx
        return result

    def range_query(self, left, right):
        return self.query(right) - self.query(left - 1)


# Example
ft = FenwickTree(5)
arr = [1, 2, 3, 4, 5]

for i, val in enumerate(arr):
    ft.update(i, val)

print(ft.range_query(1, 3))