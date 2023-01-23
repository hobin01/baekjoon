from fractions import Fraction

# 큰 쪽으로는 기울기 점점 커지면 됨
n = int(input())
arr = list(map(int, input().split()))
# grad : (i,j) 연결한 직선 기울기
grad = [[0 for _ in range(n)] for _ in range(n)]

for i in range(n-1) : 
  for j in range(i+1, n):
    g = Fraction(arr[j] - arr[i], j - i)
    grad[i][j] = g
    grad[j][i] = g

arr2 = [0 for _ in range(n)]
# 큰 쪽 체크
for i in range(n-1) :
  maximum = float(-1000000001.0)
  for j in range(i+1, n) :
    g = grad[i][j]
    g = float(g)
    if maximum < g :
      maximum = g
      arr2[i] += 1
      arr2[j] += 1

print(max(arr2))