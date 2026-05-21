from collections import defaultdict

def kosaraju(v, edges):
    graph = defaultdict(list)
    rev_graph = defaultdict(list)

    for u, w in edges:
        graph[u].append(w)
        rev_graph[w].append(u)

    visited = set()
    stack = []

    def dfs(node):
        visited.add(node)
        for nei in graph[node]:
            if nei not in visited:
                dfs(nei)
        stack.append(node)

    for i in range(v):
        if i not in visited:
            dfs(i)

    visited.clear()
    sccs = []

    def rev_dfs(node, comp):
        visited.add(node)
        comp.append(node)

        for nei in rev_graph[node]:
            if nei not in visited:
                rev_dfs(nei, comp)

    while stack:
        node = stack.pop()
        if node not in visited:
            comp = []
            rev_dfs(node, comp)
            sccs.append(comp)

    return sccs


# Example
edges = [(0,1),(1,2),(2,0),(1,3)]
print(kosaraju(4, edges))