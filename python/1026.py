n = int(input())

arr1 = list(map(int,input().split()))
arr2 = list(map(int,input().split()))

arr1.sort()
arr2.sort(reverse=True)

result = 0
for i in range(n):
    result += arr1[i] * arr2[i]
    
print(result)