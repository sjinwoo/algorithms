import sys

num = sys.stdin.readline().strip().split()
A, B, C = map(int, num)

print((A + B) % C)
print(((A % C) + (B % C)) % C)
print((A * B) % C)
print(((A % C) * (B % C)) % C)