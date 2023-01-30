from itertools import combinations

n, m = map(int, input().split())
primes = list(map(int, input().split()))
result = 0

def quotient(d):
  global m
  return m // d

# 포함배제 원리 일반화 식으로 구하면 됨
def calc(s) :
  # s : 조합 원소 
  leng = len(s)
  res = 0
  tmp = 1
  for num in s :
    tmp *= num
  if leng % 2 == 0:
    res -= quotient(tmp)
  else :
    res += quotient(tmp)
  return res

for i in range(1, n + 1) :
  li = list(combinations(primes, i))
  for s in li :
    result += calc(s)

print(result)