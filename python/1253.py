n = int(input())
arr = list(map(int, input().split()))

arr.sort()
cnt = 0

# 체크하는 수가 합을 만드는 수의 인덱스와 동일하면 안 됨
for i in range(n) : 
    start = 0
    last = n - 1
    check = arr[i]
    
    # 투 포인터로 끝점에서 돌면서 check랑 맞는지 확인
    # 오름차순 정렬된 상황
    while True :
        if start >= last :
            break
        
        if start == i:
            start += 1
            continue
        if last == i : 
            last -= 1
            continue
        
        num1 = arr[start]
        num2 = arr[last]
        
        if num1 + num2 == check :
            cnt += 1
            break
        
        if num1 + num2 < check : 
            start += 1
        else : 
            last -= 1

print(cnt)