# Johnson's Algorithm

import heapq

def dijkstra(graph, src):
    dist = {v: float('inf') for v in graph}
    dist[src] = 0
    pq = [(0, src)]

    while pq:
        d, u = heapq.heappop(pq)
        if d > dist[u]:
            continue
        for v, w in graph[u]:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                heapq.heappush(pq, (dist[v], v))
    return dist


def johnson(graph):
    new_graph = graph.copy()
    new_graph['S'] = [(v, 0) for v in graph]

    h = dijkstra(new_graph, 'S')

    reweighted = {
        u: [(v, w + h[u] - h[v]) for v, w in edges]
        for u, edges in graph.items()
    }

    all_pairs = {}
    for u in graph:
        dist = dijkstra(reweighted, u)
        all_pairs[u] = {v: dist[v] - h[u] + h[v] for v in dist}

    return all_pairs


graph = {
    'A': [('B', 1), ('C', 4)],
    'B': [('C', -2)],
    'C': [('A', 2)]
}

print(johnson(graph))