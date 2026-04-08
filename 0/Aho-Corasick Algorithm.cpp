from collections import deque, defaultdict

class AhoCorasick:
    def __init__(self):
        self.trie = [{}]
        self.fail = [0]
        self.output = defaultdict(list)

    def add_word(self, word):
        node = 0
        for ch in word:
            if ch not in self.trie[node]:
                self.trie[node][ch] = len(self.trie)
                self.trie.append({})
                self.fail.append(0)
            node = self.trie[node][ch]
        self.output[node].append(word)

    def build(self):
        queue = deque()
        for ch in self.trie[0]:
            queue.append(self.trie[0][ch])

        while queue:
            r = queue.popleft()
            for ch, u in self.trie[r].items():
                queue.append(u)
                f = self.fail[r]

                while f and ch not in self.trie[f]:
                    f = self.fail[f]

                self.fail[u] = self.trie[f].get(ch, 0)
                self.output[u] += self.output[self.fail[u]]

    def search(self, text):
        node = 0
        result = []

        for i, ch in enumerate(text):
            while node and ch not in self.trie[node]:
                node = self.fail[node]

            node = self.trie[node].get(ch, 0)

            for word in self.output[node]:
                result.append((i - len(word) + 1, word))

        return result


# Example
ac = AhoCorasick()
for w in ["he", "she", "his", "hers"]:
    ac.add_word(w)
ac.build()
print(ac.search("ahishers"))