def articulation_points(graph):
    n = len(graph)

    disc = [-1] * n
    low = [-1] * n
    parent = [-1] * n
    ap = set()

    timer = 0

    def dfs(u):
        nonlocal timer
        children = 0

        disc[u] = low[u] = timer
        timer += 1

        for v in graph[u]:
            if disc[v] == -1:
                parent[v] = u
                children += 1

                dfs(v)

                low[u] = min(low[u], low[v])

                if parent[u] == -1 and children > 1:
                    ap.add(u)

                if parent[u] != -1 and low[v] >= disc[u]:
                    ap.add(u)

            elif v != parent[u]:
                low[u] = min(low[u], disc[v])

    for i in range(n):
        if disc[i] == -1:
            dfs(i)

    return list(ap)


# Example
graph = [
    [1, 2],
    [0, 2],
    [0, 1, 3],
    [2, 4],
    [3]
]

print(articulation_points(graph))