def largest_rectangle(heights):
    stack = []
    max_area = 0
    heights.append(0)  # sentinel

    for i in range(len(heights)):
        while stack and heights[stack[-1]] > heights[i]:
            h = heights[stack.pop()]
            w = i if not stack else i - stack[-1] - 1
            max_area = max(max_area, h * w)
        stack.append(i)

    return max_area


# Example
print(largest_rectangle([2,1,5,6,2,3]))