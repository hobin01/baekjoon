n = int(input())
arr = list(map(int,input().split()))

# 3으로 나누거나 2를 곱하므로 중복 불가
def calc(num, cnt, arr, result):
    num2 = num * 2
    num3 = num // 3
    r = num % 3
    
    if cnt == len(arr):
        return result
    
    if num2 in arr:
        result.append(num2)
        return calc(num2, cnt + 1, arr, result)
    
    elif r == 0 and num3 in arr:
        result.append(num3)
        return calc(num3, cnt + 1, arr, result)
    
    else:
        result = []
        cnt = 0
        return result
        
def print_list(List):
    for i in range(len(List)):
        print(List[i], end = ' ')

for num in arr:
    result = [num]
    result = calc(num, 1, arr, result)
    
    if len(result) == len(arr):
        print_list(result)
        break