# Kosaraju's Algorithm for SCC

from collections import defaultdict

def kosaraju(V, edges):
    graph = defaultdict(list)
    reverse_graph = defaultdict(list)

    for u, v in edges:
        graph[u].append(v)
        reverse_graph[v].append(u)

    visited = [False] * V
    stack = []

    def dfs1(v):
        visited[v] = True
        for nbr in graph[v]:
            if not visited[nbr]:
                dfs1(nbr)
        stack.append(v)

    for i in range(V):
        if not visited[i]:
            dfs1(i)

    visited = [False] * V
    scc = []

    def dfs2(v, component):
        visited[v] = True
        component.append(v)
        for nbr in reverse_graph[v]:
            if not visited[nbr]:
                dfs2(nbr, component)

    while stack:
        v = stack.pop()
        if not visited[v]:
            component = []
            dfs2(v, component)
            scc.append(component)

    return scc


V = 5
edges = [(1,0),(0,2),(2,1),(0,3),(3,4)]
print("Strongly Connected Components:", kosaraju(V, edges))