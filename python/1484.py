# 투포인터로 x^2-y^2=G 만족하는 자연수 x 구하기
# x^2 - y^2 = G => x 정답 => x + 1, y + 1
# x^2 - y^2 > G => y + 1
# x^2 - y^2 < G => x + 1
# x - y = 1 인데 x^2 - y^2 > G 이면 종료

G = int(input())
x = 2
y = 1
res = []
while True : 
  if x - y == 1 :
    if (x*x - y*y) > G :
      break

  diff = (x*x - y*y) - G
  if diff == 0 :
    res.append(x)
    x += 1
    y += 1
  elif diff > 0 : 
    y += 1
  elif diff < 0 : 
    x += 1

if len(res) == 0:
  print(-1)
else :
  for r in res:
    print(r)