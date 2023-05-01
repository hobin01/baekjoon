#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long n;
vector<long long> factors;
// 오일러 파이 함수 공식 그냥 쓰기
// 소인수만 찾으면 됨

void init()
{
    cin >> n;
}

void calc_factors()
{
    long long p;
    long long num = n;
    // root(n) <= 10^6
    for(p = 2; p * p <= num; p++) {
        if(num % p == 0) {
            factors.push_back(p);
        }
        
        while(num % p == 0) {
            num /= p;
        }
    }
    
    // root(n)보다 큰 소수 남은 거
    // 또는 n이 prime인 경우
    if(num > 1)
        factors.push_back(num);
}

void euler()
{
    // n = 1 경우
    if(n == 1) {
        cout << 1;
        return;
    }
    
    // n 소수인 경우
    if(factors[0] == n) {
        cout << n - 1;
        return;
    }
    
    // 나머지 경우
    long long ans = n;
    for(auto p : factors) {
        ans /= p;
        ans *= (p - 1);
    }
    
    cout << ans;
}

int main()
{
    init();
    calc_factors();
    euler();
}