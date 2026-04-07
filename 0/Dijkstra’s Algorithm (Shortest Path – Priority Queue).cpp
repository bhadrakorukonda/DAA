import heapq

def dijkstra(n, graph, src):
    dist = [float('inf')] * n
    dist[src] = 0
    pq = [(0, src)]  # (distance, node)

    while pq:
        d, node = heapq.heappop(pq)

        if d > dist[node]:
            continue

        for nei, weight in graph[node]:
            if dist[node] + weight < dist[nei]:
                dist[nei] = dist[node] + weight
                heapq.heappush(pq, (dist[nei], nei))

    return dist


# Example
graph = {
    0: [(1,4), (2,1)],
    1: [(3,1)],
    2: [(1,2), (3,5)],
    3: []
}
print(dijkstra(4, graph, 0))