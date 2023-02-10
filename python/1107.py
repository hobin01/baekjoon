n = int(input())
m = int(input())
button = [True for _ in range(10)]
if m > 0 :
  nums = list(map(int, input().split()))
  for num in nums : 
    button[num] = False

result = min(987654321, abs(n - 100))

if n == 100 :
  print(0)
  exit()

if m == 0 :
  if n == 99 or n == 101 : 
    print(1)
    exit()
  if n == 102 : 
    print(2)
    exit()
  print(len(str(n)))
  exit()

def calc(num) :
  global result, n
  for i in range(10) :
    if button[i] == False :
      continue
    num2 = num + str(i)
    tmp = int(num2)
    leng = len(num2)
    result = min(result, abs(n - tmp) + leng)

    if leng <= 6 : 
      calc(num2)

num = ""
calc(num)
print(result)
