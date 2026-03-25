# Heavy-Light Decomposition (basic structure)

class HLD:
    def __init__(self, n):
        self.n = n
        self.graph = [[] for _ in range(n)]
        self.parent = [-1]*n
        self.depth = [0]*n
        self.size = [0]*n
        self.heavy = [-1]*n

    def add_edge(self, u, v):
        self.graph[u].append(v)
        self.graph[v].append(u)

    def dfs(self, u):
        size = 1
        max_subtree = 0
        for v in self.graph[u]:
            if v != self.parent[u]:
                self.parent[v] = u
                self.depth[v] = self.depth[u] + 1
                subtree = self.dfs(v)
                if subtree > max_subtree:
                    max_subtree = subtree
                    self.heavy[u] = v
                size += subtree
        self.size[u] = size
        return size


hld = HLD(5)
hld.add_edge(0,1)
hld.add_edge(1,2)
hld.add_edge(1,3)
hld.add_edge(3,4)

hld.dfs(0)
print("Heavy child array:", hld.heavy)