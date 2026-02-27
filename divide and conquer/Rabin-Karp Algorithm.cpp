# Rabin-Karp Algorithm

def rabin_karp(text, pattern, prime=101):
    m, n = len(pattern), len(text)
    base = 256
    h = pow(base, m-1) % prime

    p_hash = t_hash = 0
    result = []

    for i in range(m):
        p_hash = (base * p_hash + ord(pattern[i])) % prime
        t_hash = (base * t_hash + ord(text[i])) % prime

    for i in range(n - m + 1):
        if p_hash == t_hash:
            if text[i:i+m] == pattern:
                result.append(i)

        if i < n - m:
            t_hash = (base * (t_hash - ord(text[i]) * h)
                      + ord(text[i + m])) % prime
            if t_hash < 0:
                t_hash += prime

    return result


text = "GEEKS FOR GEEKS"
pattern = "GEEK"
print("Pattern found at indices:", rabin_karp(text, pattern))