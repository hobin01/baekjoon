ip = input()
ip = ip.split(':')
if len(ip) > 8 :
  ip.remove('')

zeros = 8 - len(ip)
res = []
chk = True
for s in ip :
  if len(s) > 0 :
    res.append(s)
  else :
    if chk :
      for _ in range(zeros) :
        res.append(s)
      chk = False
    res.append(s)

for i in range(8) :
  zeros = 4 - len(res[i])
  for _ in range(zeros):
    print('0', end='')
  print(res[i], end='')
  if i < 7 :
    print(':', end='')