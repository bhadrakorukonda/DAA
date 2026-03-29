import bisect

def LIS(arr):
    lis = []

    for num in arr:
        pos = bisect.bisect_left(lis, num)
        if pos == len(lis):
            lis.append(num)
        else:
            lis[pos] = num

    return len(lis)


# Example
arr = [10, 9, 2, 5, 3, 7, 101, 18]
print("Length of LIS:", LIS(arr))