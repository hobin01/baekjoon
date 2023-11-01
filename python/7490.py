def parse(s) :
    res = 0
    cur = ""
    oper = 1 # 1 : +, -1 : - 
    for c in s :
        if c.isdigit() : 
            cur += c 
        else :
            if len(cur) > 0 : 
                res += oper * int(cur)
                cur = ""
            if c == '+' :
                oper = 1 
            elif c == '-' :
                oper = -1 
    if len(cur) > 0 :
        res += oper * int(cur)
    return res 

def calc(arr) :
    res = []
    # (0, ..., 0) ~ (2, ..., 2)
    # 0 : ' ', 1 : +, 2 : -
    opers = []
    for i in range(3**(len(arr) - 1)) : 
        tmp = []
        for j in range(len(arr) - 1) :
            tmp.append(i % 3)
            i //= 3
        opers.append(tmp)
    
    for op in opers :
        s = arr[0]
        for i in range(len(op)) :
            if op[i] == 1 :
                s += "+"
                s += arr[i+1]
            elif op[i] == 2 :
                s += "-"
                s += arr[i+1]
            elif op[i] == 0 :
                s += arr[i+1]
        tmp = parse(s)
        if tmp == 0 :
            chk = []
            prevDigit = False 
            for c in s :
                if c.isdigit() :
                    if prevDigit == True :
                        chk.append(' ')
                    prevDigit = True
                else :
                    prevDigit = False 
                chk.append(c)
            res.append(''.join(chk))
    return res 

T = int(input())
for _ in range(T) : 
    N = int(input())
    arr = [str(i) for i in range(1, N+1)]
    res = calc(arr)
    res.sort()
    for r in res :
        print(r)
    print()