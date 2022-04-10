n, k = map(int,input().split())

arr = []

for i in range(n):
    arr.append(i + 1)

start = k - 1

result = []

while True:
    num = arr.pop(start)
    result.append(num)
    start += k - 1
    
    if len(arr) != 0:
        start %= len(arr)
    else:
        break
    
print_result = '<'
for i in range(n-1):
    print_result += str(result[i])
    print_result += ', '

print_result += str(result[-1])
print_result += '>'

print(print_result)