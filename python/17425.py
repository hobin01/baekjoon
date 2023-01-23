from sys import stdin

MAX = 1000001

sums = [1 for _ in range(MAX)]
# 에라토스테네스 체 응용해서 소인수분해 + 약수 합 동시 구하기
for i in range(2, MAX) :
  for j in range(i, MAX, i) : 
    sums[j] += i

# 부분합으로 구하려는 값 계산
for i in range(2, MAX) :
  sums[i] += sums[i-1]

T = int(stdin.readline().rstrip())
for _ in range(T) :
  N = int(stdin.readline().rstrip())
  print(sums[N])