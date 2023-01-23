# dfs로 가능한 개수 하나씩 체크
# nHr 이랑 다르게 합이 중복될 수 있으니까 그거 체크해줘야 함

n = int(input())
check = [False for _ in range(10000)]
nums = [1, 5, 10, 50]
res = 0

def dfs(cnt, idx, sum) :
  global res
  if cnt == 0 :
    if check[sum] == False :
      res += 1
      check[sum] = True
    return

  for i in range(idx, 4) : 
    dfs(cnt - 1, i, sum + nums[i])

dfs(n, 0, 0)
print(res)