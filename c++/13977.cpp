#include <iostream>

using namespace std;

int n, m, k;
long long mod = 1000000007;

// 400만 팩토리얼까지 다 구하고 조합 식 이용
// n 범위가 mod보다 작으므로 a^p-1=1 mod p 만족 안 하는 a는 안 나옴
// a^p-2 = a^-1 mod p

long long fac[4000001];

void init()
{
    cin >> n >> k;
}

void calc_fac()
{
    fac[0] = 1;
    fac[1] = 1;
    for(long long i = 2; i <= 4000000; i++) {
        fac[i] = (fac[i-1] * i) % mod;
    }
}

long long inv(long long num)
{
    long long res = 1;
    long long p = mod - 2;
    while(p > 0) {
        if(p & 1) {
            res *= num;
            res %= mod;
        }
        num = (num * num) % mod;
        p >>= 1;
    }
    return res;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> m;
    calc_fac();
    
    while(m--) {
        init();
        
        long long N = fac[n];
        long long N_K = fac[n-k];
        long long K = fac[k];
        
        cout << ((N * inv(N_K) % mod) * inv(K)) % mod << '\n';
    }
}