T = int(input())
for _ in range(T) :
  n = int(input())
  if n == 1 or n == 2 or n == 3 or n == 6:
    print(0)
  elif n == 4:
    print(2)
  else:
    print(1)