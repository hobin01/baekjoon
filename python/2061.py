p, k = map(int, input().split())
chk = False;
for i in range(2, k) :
  if p % i == 0 :
    print("BAD", i)
    chk = True;
    break;

if chk == False : 
  print("GOOD")