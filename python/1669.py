x, y = map(int, input().split())

def calc(x, y):
    if x == y:
        return 0
    elif x == (y - 1):
        return 1
    elif x == (y - 2):
        return 2
    else:
        return -1

if calc(x, y) != -1:
    print(calc(x, y))
else:
    sub = y - x
    cnt = 0
    while (cnt**2 < sub):
        cnt += 1
    
    if (cnt * (cnt - 1)) < sub:
        print(2 * cnt - 1)
    else:
        print(2 * cnt - 2)