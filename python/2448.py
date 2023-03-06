n = int(input())
arr = [[' ', ' '] * n for _ in range(n)]

def dfs(y, x, idx) :
  if idx == 3:
    arr[y][x] = '*'
    arr[y + 1][x - 1] = '*'
    arr[y + 1][x + 1] = '*'
    arr[y + 2][x - 2] = '*'
    arr[y + 2][x - 1] = '*'
    arr[y + 2][x + 0] = '*'
    arr[y + 2][x + 1] = '*'
    arr[y + 2][x + 2] = '*'
  else :
    next = idx // 2
    dfs(y, x, next)
    dfs(y + next, x - next, next)
    dfs(y + next, x + next, next)

dfs(0, n - 1, n)
for i in range(n) :
  print("".join(arr[i]))