# Aho-Corasick Algorithm

from collections import deque, defaultdict

class AhoCorasick:
    def __init__(self):
        self.trie = [{}]
        self.fail = [0]
        self.output = defaultdict(list)

    def add_word(self, word):
        node = 0
        for char in word:
            if char not in self.trie[node]:
                self.trie[node][char] = len(self.trie)
                self.trie.append({})
                self.fail.append(0)
            node = self.trie[node][char]
        self.output[node].append(word)

    def build(self):
        queue = deque()
        for char, nxt in self.trie[0].items():
            queue.append(nxt)

        while queue:
            r = queue.popleft()
            for char, nxt in self.trie[r].items():
                queue.append(nxt)
                f = self.fail[r]
                while f and char not in self.trie[f]:
                    f = self.fail[f]
                self.fail[nxt] = self.trie[f].get(char, 0)
                self.output[nxt] += self.output[self.fail[nxt]]

    def search(self, text):
        node = 0
        results = []
        for i, char in enumerate(text):
            while node and char not in self.trie[node]:
                node = self.fail[node]
            node = self.trie[node].get(char, 0)
            for pattern in self.output[node]:
                results.append((i - len(pattern) + 1, pattern))
        return results


ac = AhoCorasick()
patterns = ["he", "she", "his", "hers"]

for p in patterns:
    ac.add_word(p)

ac.build()
print(ac.search("ahishers"))