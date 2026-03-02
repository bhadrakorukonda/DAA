# Hopcroft-Karp Algorithm

from collections import deque, defaultdict

def hopcroft_karp(graph, n, m):
    INF = float('inf')
    pairU = [-1] * n
    pairV = [-1] * m
    dist = [0] * n

    def bfs():
        queue = deque()
        for u in range(n):
            if pairU[u] == -1:
                dist[u] = 0
                queue.append(u)
            else:
                dist[u] = INF
        d = INF

        while queue:
            u = queue.popleft()
            if dist[u] < d:
                for v in graph[u]:
                    if pairV[v] == -1:
                        d = dist[u] + 1
                    elif dist[pairV[v]] == INF:
                        dist[pairV[v]] = dist[u] + 1
                        queue.append(pairV[v])
        return d != INF

    def dfs(u):
        for v in graph[u]:
            if pairV[v] == -1 or (dist[pairV[v]] == dist[u] + 1 and dfs(pairV[v])):
                pairU[u] = v
                pairV[v] = u
                return True
        dist[u] = INF
        return False

    result = 0
    while bfs():
        for u in range(n):
            if pairU[u] == -1 and dfs(u):
                result += 1
    return result


graph = {
    0: [0, 1],
    1: [1],
    2: [0, 2]
}

print("Maximum Matching:", hopcroft_karp(graph, 3, 3))