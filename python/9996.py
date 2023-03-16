import re
n = int(input())
s1, s2 = input().rstrip().split("*")
l1 = len(s1)
l2 = len(s2)
for _ in range(n) :
  s = input()
  if len(s) < l1 + l2:
    print("NE")
  elif s[:l1] == s1 and s[-l2:] == s2:
    print("DA")
  else:
    print("NE")