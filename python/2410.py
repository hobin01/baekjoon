n = int(input())
mod = 1000000000

dp = [0 for _ in range(n+1)] 
dp[0] = 1
# dp[i] : i 만드는데 필요한 경우의 수
# 계산 위해 dp[0]=1 설정

powers = [] # n 이하 2 거듭제곱 수들
num = 1
while num <= n:
    powers.append(num)
    num  = num * 2

# 2의 거듭제곱 간격 기준으로 dp 계산
powers_len = len(powers)
for i in range(powers_len):
    for j in range(powers[i], n+1):
        dp[j] = (dp[j] + dp[j - powers[i]]) % mod
        
print(dp[n] % mod)
