T = int(input())

# a**b mod 10=?
zero = [0]
one = [1]
two = [2,4,8,6]
three = [3,9,7,1]
four = [4,6]
five = [5]
six = [6]
seven = [7,9,3,1]
eight = [8,4,2,6]
nine = [9,1]
    
mod = [zero, one, two, three, four, five, six, seven, eight, nine]

for _ in range(T):
    a, b = map(int, input().split())
    a %= 10
    b = b % len(mod[a]) - 1
    if b < 0 : b = len(mod[a]) - 1
    ans = mod[a][b]
    if ans == 0 : ans = 10
    print(ans)    