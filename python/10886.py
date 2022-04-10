N=int(input())
y=0;n=0
for _ in range(N):
    s=input()
    if s=="1":
        y += 1
    else:
        n += 1
if y > n:
    print("Junhee is cute!")
else:
    print("Junhee is not cute!")