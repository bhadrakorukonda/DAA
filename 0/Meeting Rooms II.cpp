import heapq

def min_meeting_rooms(intervals):
    if not intervals:
        return 0

    intervals.sort(key=lambda x: x[0])

    heap = []
    heapq.heappush(heap, intervals[0][1])

    for start, end in intervals[1:]:
        if start >= heap[0]:
            heapq.heappop(heap)

        heapq.heappush(heap, end)

    return len(heap)


# Example
intervals = [[0,30],[5,10],[15,20]]
print(min_meeting_rooms(intervals))