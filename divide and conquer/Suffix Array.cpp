# Suffix Array (naive construction)

def build_suffix_array(s):
    suffixes = [(s[i:], i) for i in range(len(s))]
    suffixes.sort()
    return [idx for (_, idx) in suffixes]


def build_lcp(s, sa):
    n = len(s)
    rank = [0]*n
    lcp = [0]*n

    for i in range(n):
        rank[sa[i]] = i

    k = 0
    for i in range(n):
        if rank[i] == 0:
            continue
        j = sa[rank[i]-1]
        while i+k < n and j+k < n and s[i+k] == s[j+k]:
            k += 1
        lcp[rank[i]] = k
        if k > 0:
            k -= 1

    return lcp


s = "banana"
sa = build_suffix_array(s)
lcp = build_lcp(s, sa)

print("Suffix Array:", sa)
print("LCP Array:", lcp)