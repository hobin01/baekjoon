n = int(input())

# 감소하는 수들 리스트 오름차순
decrease = [0,1,2,3,4,5,6,7,8,9]

# decrease를 큐처럼 생각해서
# 하나 씩 pop한 다음
# r in [0, pop 한 값의 1의 자리 (pop % 10) ) 동안
# 10 * pop + r 을 다시 큐에 넣어줌
# ex. 0 => [0, 0) => 없음
# 1 => [0, 1) => 10 push
# 2 => [0, 2) => 20, 21 push
# ... 321 => [0, 1) => 3210 push
# 이런 식으로 오름차순으로 넣을 수 있음
# 줄어드는 수 최대값은 9876543210
# 도달하면 while문 끝

result_idx = 0
result = 0

while len(decrease) != 0:
    pop_num = decrease.pop(0)
    result_idx += 1
    result = pop_num
    
    if result_idx == n:
        break
    
    for r in range(0, pop_num % 10):
        decrease.append(10 * pop_num + r)
    
if result_idx < n:
    print(-1)

elif result_idx == n:
    print(result)
