# 그리디
# 점수 순 정렬
# 그리고 마감일 칸 비어있으면 거기에 넣기
# (해당 일에 딱 하겠다는 뜻)
# 마감일 칸 차있으면 (더 큰 점수 얻는 경우 존재)
# 그 전 칸 중 가장 가까운 빈 칸에 넣기 
# (최대한 늦게 하겠다는 뜻)

N = int(input())
arr = []
for _ in range(N) :
    d, w = map(int, input().split())
    arr.append((w, d))
arr.sort(reverse=True)

res = [0 for _ in range(1001)]
for a in arr :
    w = a[0]
    d = a[1]
    if res[d] == 0 :
        res[d] = w 
    else :
        idx = d-1 
        while idx > 0 :
            if res[idx] == 0 :
                res[idx] = w 
                break 
            idx -= 1 

print(sum(res))