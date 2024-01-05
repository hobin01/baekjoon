#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// n=1 : 답 1 
// n : miller rabin prime test 로 소수인지 판단
// 소수면 답 n-1 
// 아니면 pollard rho 로 소인수분해 후 euler phi function 계산 

// x^y mod p 
long long power(__int128 x, __int128 y, __int128 p)
{
    __int128 res = 1;
    x %= p;
    
    while(y != 0) {
        if(y & 1)
            res = (res * x) % p;
        y >>= 1;
        x = (x * x) % p;
    }
    
    return (long long)res;
}

// miller rabin test 
// check n 
bool miller_rabin_test(long long d, long long n)
{
    srand(time(NULL));
    
    long long a = (rand() % (n-2)) + 2;
    long long x = power(a, d, n);
    
    if(x == 1 || x == (n-1))
        return true;
    
    while(d != (n-1)) {
        x = power(x, 2, n);
        d <<= 1;
        
        if(x == 1)
            return false;
        if(x == n-1)
            return true;
    }
    
    return false;
}

// is n prime ?
// k : miller rabin test loop 
bool prime_check(long long n, int k)
{
    if(n == 1)
        return false;
        
    long long basePrimes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for(auto i : basePrimes) {
        if(n == i)
            return true;
        if(n % i == 0)
            return false;
    }
    
    long long d = n - 1;
    while(d & 1 == 0)
        d >>= 1;
    
    for(int i = 0; i < k; i++) {
        if(miller_rabin_test(d, n) == false)
            return false;
    }
    
    return true;
}

// gcd(a, b)
long long gcd(long long a, long long b)
{
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

// pollard rho alg 
long long pollard_rho(long long n, int k)
{
    if(n == 1)
        return n;
    if(n & 1 == 0)
        return 2;
        
    srand(time(NULL));
    
    long long x = (rand() % (n-2)) + 2;
    long long y = x;
    long long c = (rand() % (n-1)) + 1;
    long long d = 1;
    
    while(d == 1) {
        x = (power(x, 2, n) + c) % n;
        y = (power(y, 2, n) + c) % n;
        y = (power(y, 2, n) + c) % n;
        d = gcd(abs(x - y), n);
        
        if(d == n) {
            x = (rand() % (n-2)) + 2;
            y = x;
            c = (rand() % (n-1)) + 1;
            d = 1;
        }
    }
    
    if(prime_check(d, k))
        return d;
    else 
        return pollard_rho(d, k);
}

// factorize from pollard rho 
vector<long long> calc_factors(long long n, int k)
{
    vector<long long> res;
    
    if(n % 2 == 0) {
        res.push_back(2);
        while(n % 2 == 0) 
            n >>= 1;
    }
    
    while(n != 1) {
        if(prime_check(n, k)) {
            res.push_back(n);
            break;
        }
        
        long long factor = pollard_rho(n, k);
        
        res.push_back(factor);
        
        while((n % factor) == 0)
            n /= factor;
    }
    
    return res;
}

// euler phi function
// phi(n) = n * (multiply i=1 to r (1-1/pi))
// k1, k2, .., kr are the number of factors
long long euler_phi(long long n, int k)
{
    if(n == 1)
        return 1;
    if(prime_check(n, k))
        return n-1;
    
    vector<long long> factors = calc_factors(n, k);
    
    long long res = n;
    for(auto f : factors) {
        res -= (res / f);
    }
    
    return res;
}

int main()
{
    long long n;
    cin >> n;
    
    int k = 10;
    
    cout << euler_phi(n, k);
}