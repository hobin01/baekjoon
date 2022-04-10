str1 = input()
str2 = input()
mod = 999979
ans = 0

primes = {}

idx = 0
for i in range(2,1000):
    flag = 1
    for j in range(2,int(i**0.5)):
        if i % j == 0:
            flag = 0
            break
    if flag == 1:
        primes[idx] = i
        idx += 1

hash_list = [[] for _ in range(mod)]
    
for i in range(len(str2)):
    hash1 = 1
    hash2 = 1
    for j in range(i,len(str2)):
        length = j - i + 1
        chr_idx = ord(str2[j]) - ord('a')
        num = primes[chr_idx]
        hash1 *= num
        hash1 %= mod
        hash2 *= primes[chr_idx + 26]
        hash2 %= mod
        hash_list[hash1].append((hash2, length))

for i in range(len(str1)):
    hash1 = 1
    hash2 = 1
    for j in range(i, len(str1)):
        length = j - i + 1
        chr_idx = ord(str1[j]) - ord('a')
        num = primes[chr_idx]
        hash1 *= num
        hash1 %= mod
        hash2 *= primes[chr_idx + 26]
        hash2 %= mod
        
        for k in range(len(hash_list[hash1])):
            if(hash_list[hash1][k] == (hash2, length)):
                ans = max(ans, length)

print(ans)
        
        