t = int(input())
for _ in range(t) :
    n = int(input())
    arr = list(map(int, input().split()))
    d = dict()
    for a in arr : 
        d[a] = 1
    m = int(input())
    arr2 = list(map(int, input().split()))
    for a in arr2 :
        if a in d.keys() :
            print(1)
        else :
            print(0)
        