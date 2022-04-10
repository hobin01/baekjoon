n = int(input())
arr = list(map(int, input().split()))
dp = [0 for _ in range(n)]
for i in range(n):
    dp[i] = arr[i]
for i in range(n):
    for j in range(i, n):
        if arr[i] < arr[j]:
            if dp[i] + arr[j] > dp[j]:
                dp[j] = dp[i] + arr[j]

result = 0
for i in range(n):
    result = max(result, dp[i])
print(result)
