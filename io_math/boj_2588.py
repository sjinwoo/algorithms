import sys

a = sys.stdin.readline().strip()
b = sys.stdin.readline().strip()
res = 0

for i in range(len(b)):
    print(int(a)*int(b[2 - i]))
    res += int(a)*int(b[2 - i]) * 10^i
    print(res)
print(res)