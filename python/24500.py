n = int(input())
bits = bin(n)[2:]
arr = []
for i in range(len(bits)) :
    if bits[i] == '0' :
        arr.append(i)
if len(arr) == 0 :
    print(1)
    print(n)
else :
    bits2 = ['0' for _ in range(len(bits))]
    for a in arr :
        bits2[a] = '1'
    bits2 = ''.join(bits2)
    n2 = int(bits2, 2)
    print(2)
    print(n2)
    print(n)