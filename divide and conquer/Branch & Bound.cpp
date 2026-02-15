# TSP using Branch and Bound
import sys

INF = sys.maxsize

def tsp(graph, visited, curr_pos, n, count, cost, ans):
    if count == n and graph[curr_pos][0]:
        ans[0] = min(ans[0], cost + graph[curr_pos][0])
        return

    for i in range(n):
        if not visited[i] and graph[curr_pos][i]:
            visited[i] = True
            tsp(graph, visited, i, n, count + 1,
                cost + graph[curr_pos][i], ans)
            visited[i] = False


def solve_tsp(graph):
    n = len(graph)
    visited = [False] * n
    visited[0] = True
    ans = [INF]

    tsp(graph, visited, 0, n, 1, 0, ans)
    return ans[0]


graph = [
    [0, 10, 15, 20],
    [10, 0, 35, 25],
    [15, 35, 0, 30],
    [20, 25, 30, 0]
]

print("Minimum cost:", solve_tsp(graph))