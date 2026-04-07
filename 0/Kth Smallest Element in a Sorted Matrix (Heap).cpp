import heapq

def kth_smallest(matrix, k):
    n = len(matrix)
    heap = []

    for i in range(min(n, k)):
        heapq.heappush(heap, (matrix[i][0], i, 0))

    for _ in range(k):
        val, r, c = heapq.heappop(heap)
        if c + 1 < len(matrix[0]):
            heapq.heappush(heap, (matrix[r][c+1], r, c+1))

    return val


# Example
matrix = [
    [1, 5, 9],
    [10,11,13],
    [12,13,15]
]
print(kth_smallest(matrix, 8))