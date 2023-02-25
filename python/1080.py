def flip(y, x, mat) :
  # i, j부터 3x3 뒤집기
  for i in range(y, y + 3) :
    for j in range(x, x + 3) :
      mat[i][j] ^= 1

n, m = map(int, input().split())  
mat1 = []
mat2 = []
for _ in range(n) :
  row = list(map(int, list(input())))
  mat1.append(row)
for _ in range(n) :
  row = list(map(int, list(input())))
  mat2.append(row)

if n < 3 or m < 3 :
  chk = True
  for i in range(n) :
    for j in range(m) :
      if mat1[i][j] != mat2[i][j] :
        chk = False
        break
    if chk == False :
      break
  if chk == True :
    print(0)
    exit()
  else :
    print(-1)
    exit()

res = 0
for i in range(n - 2) :
  for j in range(m - 2) :
    if mat1[i][j] != mat2[i][j] :
      res += 1
      flip(i, j, mat1)

chk = True
for i in range(n) :
  for j in range(m) :
    if mat1[i][j] != mat2[i][j] :
      chk = False
      print(-1)
      exit()

if chk == True :
  print(res)