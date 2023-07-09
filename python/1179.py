import sys
sys.setrecursionlimit(10**9)

def g(n, k) : 
    if n == 1 :
        return 0
    elif n > 1 and n < k :
        return (g(n-1, k) + k) % n
    else :
        h = g(n-(n//k), k) - (n % k)
        if h < 0 :
            return h+n
        else :
            return h+(h//(k-1))
            
n, k = map(int, input().split())

if k == 1 :
    print(n)
else :
    print(g(n,k)+1)