# Huffman Coding
import heapq

class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq


def print_codes(root, code):
    if root is None:
        return
    if root.char is not None:
        print(root.char, ":", code)
    print_codes(root.left, code + "0")
    print_codes(root.right, code + "1")


def huffman(chars, freqs):
    heap = []
    for i in range(len(chars)):
        heapq.heappush(heap, Node(chars[i], freqs[i]))

    while len(heap) > 1:
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)
        merged = Node(None, left.freq + right.freq)
        merged.left = left
        merged.right = right
        heapq.heappush(heap, merged)

    print_codes(heap[0], "")


chars = ['a', 'b', 'c', 'd', 'e', 'f']
freqs = [5, 9, 12, 13, 16, 45]

huffman(chars, freqs)