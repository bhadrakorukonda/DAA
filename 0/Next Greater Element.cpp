def next_greater(nums):
    stack = []
    result = [-1] * len(nums)

    for i in range(len(nums)-1, -1, -1):
        while stack and stack[-1] <= nums[i]:
            stack.pop()

        if stack:
            result[i] = stack[-1]

        stack.append(nums[i])

    return result


# Example
print(next_greater([4,5,2,10]))