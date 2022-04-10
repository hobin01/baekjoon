import math

n = int(input())
arr = []
for i in range(n):
    num = int(input())
    arr.append(num)

result = 0
gcd = arr[1] - arr[0]

for i in range(1, n - 1):
    gcd = math.gcd(gcd, arr[i + 1] - arr[i])
    
for i in range(n - 1):
    result += (arr[i + 1] - arr[i])//gcd - 1
    
print(result)