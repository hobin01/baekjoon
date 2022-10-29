import itertools

s = input()
sLen = len(s)
result = ""

arr = [i for i in range(1, sLen)] # 1 ~ sLen-1
comb = itertools.combinations(arr, 2) # nC2

for c in comb : 
  first = c[0]
  second = c[1]

  sub1 = s[0:first]
  sub2 = s[first:second]
  sub3 = s[second:]
  
  reverse1 = sub1[::-1]
  reverse2 = sub2[::-1]
  reverse3 = sub3[::-1]

  tmp = reverse1 + reverse2 + reverse3
  
  if len(result) == 0:
    result = tmp
  else :
    if result > tmp : 
      result = tmp

print(result)