class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        px, py = self.find(x), self.find(y)
        if px == py:
            return False
        if self.rank[px] < self.rank[py]:
            self.parent[px] = py
        else:
            self.parent[py] = px
            if self.rank[px] == self.rank[py]:
                self.rank[px] += 1
        return True


def kruskal(n, edges):
    edges.sort(key=lambda x: x[2])  # sort by weight
    dsu = DSU(n)
    mst_weight = 0
    mst_edges = []

    for u, v, w in edges:
        if dsu.union(u, v):
            mst_weight += w
            mst_edges.append((u, v, w))

    return mst_weight, mst_edges


# Example
edges = [(0,1,4), (0,2,3), (1,2,1), (1,3,2), (2,3,4)]
print(kruskal(4, edges))