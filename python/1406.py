import sys
 
str1 = list(sys.stdin.readline().rstrip())
str2 = []

n = int(input())

for i in range(n):
    
    line = sys.stdin.readline().rstrip()
    
    if line[0] == 'L':
        if str1: 
            str2.append(str1.pop())
        else: 
            continue
    elif line[0] == 'D':
        if str2: 
            str1.append(str2.pop())
        else: 
            continue
    elif line[0] == 'B':
        if str1: 
            str1.pop()
        else: 
            continue
    elif line[0] == 'P':
        str1.append(line[2])
        
print(''.join(str1 + list(reversed(str2))))