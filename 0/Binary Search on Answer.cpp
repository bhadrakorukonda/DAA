def can_place(stalls, k, dist):
    count = 1
    last_pos = stalls[0]

    for i in range(1, len(stalls)):
        if stalls[i] - last_pos >= dist:
            count += 1
            last_pos = stalls[i]
        if count >= k:
            return True

    return False


def aggressive_cows(stalls, k):
    stalls.sort()
    low, high = 1, stalls[-1] - stalls[0]
    result = 0

    while low <= high:
        mid = (low + high) // 2
        if can_place(stalls, k, mid):
            result = mid
            low = mid + 1
        else:
            high = mid - 1

    return result


# Example
print(aggressive_cows([1,2,4,8,9], 3))