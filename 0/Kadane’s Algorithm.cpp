def kadane(arr):
    max_sum = arr[0]
    curr_sum = arr[0]

    for i in range(1, len(arr)):
        curr_sum = max(arr[i], curr_sum + arr[i])
        max_sum = max(max_sum, curr_sum)

    return max_sum


# Example
arr = [-2,1,-3,4,-1,2,1,-5,4]
print(kadane(arr))