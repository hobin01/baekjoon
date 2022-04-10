n = int(input())
num = list(map(int,input().split()))
m = int(input())

low = 0
high = max(num)

while low <= high:
    mid = (low + high) // 2
    tmp = 0
    
    for i in range(n):
        if num[i] >= mid:
            tmp += mid
        else:
            tmp += num[i]
    
    if tmp <= m:
        low = mid + 1
    else:
        high = mid - 1

print(high)