a, b = map(str,input().split())

b = int(b)
num = 0
idx = 0
dot = 0 

for x in range(len(a) - 1, -1, -1) :
    if a[x] != '.':
        num += int(a[x]) * (10 ** idx)
        idx += 1 
    else :
        dot = idx 

num = num ** b 
dot = dot * b 

stringNum = str(num)

if len(stringNum) <= dot :
    stringNum = ("0" * (dot - len(stringNum) + 1)) + stringNum
    
integer = stringNum[ : len(stringNum) - dot]
floating = stringNum[len(stringNum) - dot : ]

ans = integer + "." + floating 
print(ans)
