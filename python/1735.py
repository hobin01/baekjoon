from fractions import Fraction
a, b = map(int, input().split())
c, d = map(int, input().split())
e = Fraction(a, b)
f = Fraction(c, d)
g = str(e + f).split('/')
if len(g) == 1:
  g.append('1')
res = g[0] + ' ' + g[1]
print(res)