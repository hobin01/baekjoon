dp_min = [0 for _ in range(101)]
dp_max = [0 for _ in range(101)]

dp_min[2], dp_max[2] = 1, 1
dp_min[3], dp_max[3] = 7, 7
dp_min[4], dp_max[4] = 4, 11
dp_min[5], dp_max[5] = 2, 71
dp_min[6], dp_max[6] = 0, 111
dp_min[7], dp_max[7] = 8, 711 
dp_min[8], dp_max[8] = 10, 1111

# dp 먼저 구하고 그냥 호출시키기 
for i in range(9, 101) : 
    tmp_max = 0
    for j in range(2, i - 1) : 
        tmp = dp_max[i-j] * 10 + dp_max[j]
        tmp = int(''.join(sorted(list(str(tmp)), reverse=True)))
        tmp_max = max(tmp_max, tmp)
    dp_max[i] = tmp_max

min_nums = [dp_min[i] for i in range(9)]
dp_min[6] = 6
    
for i in range(9, 101) : 
    tmp_min = 99999999999999999999999
    for j in range(2, 8) :
        tmp = dp_min[i-j] * 10 + min_nums[j]
        tmp_min = min(tmp_min, tmp)
    dp_min[i] = tmp_min

T = int(input())

for _ in range(T) : 
    n = int(input())
    print(dp_min[n], dp_max[n])