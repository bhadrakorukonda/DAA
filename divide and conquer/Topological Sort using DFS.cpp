# Topological Sort using DFS

from collections import defaultdict

def topological_sort(V, edges):
    graph = defaultdict(list)
    for u, v in edges:
        graph[u].append(v)

    visited = [False] * V
    stack = []

    def dfs(v):
        visited[v] = True
        for nbr in graph[v]:
            if not visited[nbr]:
                dfs(nbr)
        stack.append(v)

    for i in range(V):
        if not visited[i]:
            dfs(i)

    return stack[::-1]


V = 6
edges = [
    (5, 2), (5, 0),
    (4, 0), (4, 1),
    (2, 3), (3, 1)
]

print("Topological Order:", topological_sort(V, edges))