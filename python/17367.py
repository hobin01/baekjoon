n = int(input())
dp = [ [ [ [0 for _ in range(7)] for _ in range(7) ] for _ in range(7) ] for _ in range(n) ]

# dp[i][j][k][l] : 횟수 i 번 남았을 때 마지막 수들이 j,k,l 인 케이스 
# 기대값이 높으면 업데이트, 아니면 기존 수 그대로 
# 0번 남을 시 그냥 계산 
# dp[i][j][k][l] = max(sum(dp[i-1][k][l])/6, dp[i-1][j][k][l])
# 위와 같은 이유는 1번 더 던지면 k, l 이 앞으로 땡겨지기 때문

# 기회 0번 남은 케이스 
for j in range(1, 7) : 
    for k in range(1, 7) : 
        for l in range(1, 7) : 
            tmp = 0 
            if j == k and k == l :
                tmp = 10000 + j * 1000 
            elif j != k and k != l and l != j :
                tmp = max(j, k, l) * 100 
            else :
                if j == k :
                    tmp = 1000 + j * 100 
                elif k == l :
                    tmp = 1000 + k * 100 
                elif l == j :
                    tmp = 1000 + l * 100 
            dp[0][j][k][l] = tmp

# 나머지 케이스 
for i in range(1, n) : 
    for j in range(1, 7) : 
        for k in range(1, 7) : 
            for l in range(1, 7) : 
                dp[i][j][k][l] = max(sum(dp[i-1][k][l])/6, dp[i-1][j][k][l])
                
ans = 0
for k in range(1, 7) : 
    for l in range(1, 7) : 
        ans += sum(dp[n-3][k][l])
        
print(ans/216)