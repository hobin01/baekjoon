N = int(input())
result = []

def hanoi(num, _from, to, via) :
    if num == 1:
        result.append((_from, to))
        return
    hanoi(num - 1, _from, via, to)
    result.append((_from, to))
    hanoi(num - 1, via, to, _from)
    
if N > 20 :
    print(2**N - 1)
else :
    hanoi(N, 1, 3, 2)
    K = len(result)
    print(K)
    for r in result :
        print(r[0], end=' ')
        print(r[1])