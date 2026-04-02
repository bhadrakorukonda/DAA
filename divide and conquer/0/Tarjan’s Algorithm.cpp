def tarjans_scc(graph):
    n = len(graph)
    ids = [-1] * n
    low = [0] * n
    on_stack = [False] * n
    stack = []
    id_counter = 0
    sccs = []

    def dfs(at):
        nonlocal id_counter
        stack.append(at)
        on_stack[at] = True
        ids[at] = low[at] = id_counter
        id_counter += 1

        for to in graph[at]:
            if ids[to] == -1:
                dfs(to)
                low[at] = min(low[at], low[to])
            elif on_stack[to]:
                low[at] = min(low[at], ids[to])

        if ids[at] == low[at]:
            scc = []
            while True:
                node = stack.pop()
                on_stack[node] = False
                scc.append(node)
                if node == at:
                    break
            sccs.append(scc)

    for i in range(n):
        if ids[i] == -1:
            dfs(i)

    return sccs


# Example
graph = [[1], [2], [0, 3], [4], []]
print(tarjans_scc(graph))
