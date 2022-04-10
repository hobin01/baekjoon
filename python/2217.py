n = int(input())
rope = []

for i in range(n):
    num = int(input())
    rope.append(num)
    
rope.sort()

result = 0

for i in range(n):
    check_size = rope[i]
    result = max(result, check_size * (n - i))

print(result)
          