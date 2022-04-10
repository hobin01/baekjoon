s = int(input())

x = (-1 + (1 + 4 * 2 * s) ** 0.5) / 2
x = int(x)

if s - (x*(x+1)) > x:
    print(x+1)
else:
    print(x)