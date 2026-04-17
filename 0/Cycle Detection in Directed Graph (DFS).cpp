def has_cycle(n, graph):
    visited = [0] * n  # 0 = unvisited, 1 = visiting, 2 = visited

    def dfs(node):
        if visited[node] == 1:
            return True
        if visited[node] == 2:
            return False

        visited[node] = 1

        for nei in graph[node]:
            if dfs(nei):
                return True

        visited[node] = 2
        return False

    for i in range(n):
        if visited[i] == 0:
            if dfs(i):
                return True

    return False


# Example
graph = [[1], [2], [0], [4], []]
print(has_cycle(5, graph))