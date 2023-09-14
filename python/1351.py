n, p, q = map(int, input().split())
if n == 0 :
    print(1)
    exit(0)
    
d = dict()
d[0] = 1

def calc(num) : 
    global p, q
    if num not in d :
        d[num] = 0
    
    ip = int(num / p)
    iq = int(num / q)
    
    if ip not in d :
        d[num] += calc(ip)
    else :
        d[num] += d[ip]
        
    if iq not in d :
        d[num] += calc(iq)
    else :
        d[num] += d[iq]
    
    return d[num]
    
print(calc(n))