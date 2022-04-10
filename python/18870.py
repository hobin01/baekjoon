import sys

n = int(sys.stdin.readline().rstrip())
arr = list(map(int,sys.stdin.readline().split()))
arr2 = sorted(arr)
result = []

# 정렬된 리스트 원소 중복 제거
arr3 = []
arr3.append(arr2[0])

for num in arr2:
    if arr3[-1] == num:
        continue
    else:
        arr3.append(num)

# index 찾는게 오래 걸린다
# dict로 바꾸자
dict1 = {}
for i in range(len(arr3)):
    dict1[arr3[i]] = i

# index 찾기
for num in arr:
    idx = dict1[num]
    result.append(idx)
    
for idx in result:
    print(idx, end=' ')