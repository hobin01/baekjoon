from sys import stdin, stdout
# 100만까지 소수 걍 구한 다음에 100만까지 골드파흐 파티션 다 구하기
maxNum = 1000000
primes = [True for _ in range(maxNum)]
primes[0] = False
primes[1] = False
for i in range(1000) : 
  if primes[i] == False:
    continue
  for j in range(i * 2, maxNum, i) : 
    primes[j] = False

T = int(stdin.readline())
for _ in range(T) :
  num = int(stdin.readline())
  res = 0
  for i in range(maxNum) : 
    if i > num // 2 :
      break
    if primes[i] == True :
      if primes[num - i] == True :
        res += 1
  stdout.write(str(res) + "\n")