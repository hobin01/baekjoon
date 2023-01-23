n, k = map(int, input().split())
MAX = 500001
bro = [-1 for _ in range(MAX)]
subin = [[-1 for _ in range(MAX)] for _ in range(2)]

subin[0][n] = 0
bro[k] = 0

q = [(n, 0)]
res = -1

while True:
  if len(q) == 0:
    break
  
  front = q.pop(0)
  pos = front[0]
  t = front[1]

  nposs = [pos + 1, pos - 1, pos * 2]
  for npos in nposs:
    if npos >= 0 and npos < MAX:
      if subin[(t + 1) % 2][npos] == -1 :
        subin[(t + 1) % 2][npos] = t + 1
        q.append((npos, t + 1))

cur = k
for i in range(MAX) :
  cur += i
  if cur >= MAX :
    break
  if subin[i % 2][cur] != -1 and subin[i % 2][cur] <= i:
    res = i
    break
    
print(res)