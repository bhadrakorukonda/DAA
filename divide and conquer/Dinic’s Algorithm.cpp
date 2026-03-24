# Dinic's Algorithm for Max Flow

from collections import deque

class Dinic:
    def __init__(self, n):
        self.n = n
        self.graph = [[] for _ in range(n)]

    def add_edge(self, u, v, cap):
        self.graph[u].append([v, cap, len(self.graph[v])])
        self.graph[v].append([u, 0, len(self.graph[u]) - 1])

    def bfs(self, s, t, level):
        queue = deque([s])
        level[s] = 0
        while queue:
            u = queue.popleft()
            for v, cap, rev in self.graph[u]:
                if cap > 0 and level[v] < 0:
                    level[v] = level[u] + 1
                    queue.append(v)
        return level[t] >= 0

    def dfs(self, u, t, flow, level, ptr):
        if u == t:
            return flow
        for i in range(ptr[u], len(self.graph[u])):
            v, cap, rev = self.graph[u][i]
            if cap > 0 and level[v] == level[u] + 1:
                pushed = self.dfs(v, t, min(flow, cap), level, ptr)
                if pushed:
                    self.graph[u][i][1] -= pushed
                    self.graph[v][rev][1] += pushed
                    return pushed
            ptr[u] += 1
        return 0

    def max_flow(self, s, t):
        flow = 0
        level = [-1] * self.n

        while self.bfs(s, t, level):
            ptr = [0] * self.n
            pushed = self.dfs(s, t, float('inf'), level, ptr)
            while pushed:
                flow += pushed
                pushed = self.dfs(s, t, float('inf'), level, ptr)
            level = [-1] * self.n

        return flow


dinic = Dinic(6)
dinic.add_edge(0,1,16)
dinic.add_edge(0,2,13)
dinic.add_edge(1,2,10)
dinic.add_edge(2,1,4)
dinic.add_edge(1,3,12)
dinic.add_edge(3,2,9)
dinic.add_edge(2,4,14)
dinic.add_edge(4,3,7)
dinic.add_edge(3,5,20)
dinic.add_edge(4,5,4)

print("Max Flow:", dinic.max_flow(0,5))