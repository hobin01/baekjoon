m, n = map(int, input().split())
print(2*(m-1) if m<=n else 2*(n-1)+1)
ans = [0, 0]
if m == n :
  if m % 2 == 0:
    ans[0] = m // 2 + 1
    ans[1] = m // 2
  else :
    ans[0] = m // 2 + 1
    ans[1] = m // 2 + 1
else :
  k = min(m, n)
  if k % 2 == 0:
    ans[0] = k - k // 2 + 1
    ans[1] = k - k // 2
  else :
    ans[0] = m - k // 2
    ans[1] = n - k // 2

print(ans[0], end='')
print(' ', end='')
print(ans[1], end='')