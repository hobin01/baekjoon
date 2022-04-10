a,d, k = map(int, input().split())
sum = 0

a = float(a)
d = float(d) / 100
k = float(k) / 100

sum = a * d 
tmp_d = 1 - d 
tmp_a = a 
d = d * (1 + k)
a += tmp_a 

while d < 1 :
    sum += (a * tmp_d * d )
    tmp_d *= (1 - d)
    d *= (1 + k)
    a += tmp_a 
    
sum += (a * tmp_d)

print(sum)