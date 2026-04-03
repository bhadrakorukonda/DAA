def rabin_karp(text, pattern):
    d = 256
    q = 101  # prime number
    n, m = len(text), len(pattern)
    h = pow(d, m-1) % q

    p_hash = 0
    t_hash = 0

    for i in range(m):
        p_hash = (d * p_hash + ord(pattern[i])) % q
        t_hash = (d * t_hash + ord(text[i])) % q

    result = []

    for i in range(n - m + 1):
        if p_hash == t_hash:
            if text[i:i+m] == pattern:
                result.append(i)

        if i < n - m:
            t_hash = (d * (t_hash - ord(text[i]) * h) + ord(text[i+m])) % q
            if t_hash < 0:
                t_hash += q

    return result


# Example
print(rabin_karp("ababcabcabababd", "ababd"))