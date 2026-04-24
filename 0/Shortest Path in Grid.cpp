from collections import deque

def shortest_path(grid):
    rows, cols = len(grid), len(grid[0])
    queue = deque([(0, 0, 0)])  # (r, c, distance)
    visited = set((0, 0))

    directions = [(1,0), (-1,0), (0,1), (0,-1)]

    while queue:
        r, c, dist = queue.popleft()

        if grid[r][c] == 1:
            return dist

        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            if 0 <= nr < rows and 0 <= nc < cols and (nr, nc) not in visited:
                visited.add((nr, nc))
                queue.append((nr, nc, dist + 1))

    return -1


# Example
grid = [
    [0,0,0],
    [1,0,1],
    [0,0,1]
]
print(shortest_path(grid))