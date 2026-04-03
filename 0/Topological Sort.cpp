from collections import deque

def topo_sort_kahn(n, edges):
    graph = [[] for _ in range(n)]
    indegree = [0] * n

    for u, v in edges:
        graph[u].append(v)
        indegree[v] += 1

    queue = deque([i for i in range(n) if indegree[i] == 0])
    topo_order = []

    while queue:
        node = queue.popleft()
        topo_order.append(node)

        for nei in graph[node]:
            indegree[nei] -= 1
            if indegree[nei] == 0:
                queue.append(nei)

    if len(topo_order) != n:
        return "Cycle detected"

    return topo_order


# Example
edges = [(5,2), (5,0), (4,0), (4,1), (2,3), (3,1)]
print(topo_sort_kahn(6, edges))