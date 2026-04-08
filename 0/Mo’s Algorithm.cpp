import math

def mos_algorithm(arr, queries):
    block = int(math.sqrt(len(arr)))
    queries = sorted(queries, key=lambda x: (x[0]//block, x[1]))

    curr_l, curr_r = 0, 0
    curr_sum = 0
    answers = [0]*len(queries)

    for i, (l, r) in enumerate(queries):
        while curr_r <= r:
            curr_sum += arr[curr_r]
            curr_r += 1

        while curr_r > r+1:
            curr_r -= 1
            curr_sum -= arr[curr_r]

        while curr_l < l:
            curr_sum -= arr[curr_l]
            curr_l += 1

        while curr_l > l:
            curr_l -= 1
            curr_sum += arr[curr_l]

        answers[i] = curr_sum

    return answers


# Example
arr = [1, 3, 2, 7, 5]
queries = [(0,2), (1,3), (2,4)]
print(mos_algorithm(arr, queries))