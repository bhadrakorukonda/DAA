def z_algorithm(s):
    n = len(s)
    z = [0]*n
    l, r = 0, 0

    for i in range(1, n):
        if i <= r:
            z[i] = min(r-i+1, z[i-l])

        while i+z[i] < n and s[z[i]] == s[i+z[i]]:
            z[i] += 1

        if i+z[i]-1 > r:
            l, r = i, i+z[i]-1

    return z


def search(text, pattern):
    concat = pattern + "$" + text
    z = z_algorithm(concat)
    result = []

    for i in range(len(z)):
        if z[i] == len(pattern):
            result.append(i - len(pattern) - 1)

    return result


# Example
print(search("ababcabcabababd", "ababd"))