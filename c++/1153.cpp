#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <stdlib.h>

using namespace std;

// 골드바흐 추측 : 4 이상 짝수는 소수 2개 합으로 표현 가능 
// 4개 소수 합으로 해야하므로 
// 1~7은 -1
// 8 이상 중 짝수면 답에 2,2 넣고 나머지 소수 2개 구하기 
// 홀수면 답에 2,3 넣고 나머지 소수 2개 구하기 

int n;
bool primes[1000001]; // 소수면 true
vector<int> res; // 답 

void init()
{
    cin >> n;
    
    if(n < 8) {
        cout << -1;
        exit(0);
    }
}

void calc_primes()
{
    memset(primes, true, sizeof(primes));
    primes[0] = false;
    primes[1] = false;
    
    for(int i = 2; i <= 1000; i++) {
        if(primes[i] == false)
            continue;
        for(int j = i * 2; j <= 1000000; j += i) {
            primes[j] = false;
        }
    }
}

void calc_res()
{
    if(n % 2 == 0) {
        res.push_back(2);
        res.push_back(2);
        n -= 4;
    }
    else {
        res.push_back(2);
        res.push_back(3);
        n -= 5;
    }
    
    for(int i = 2; i <= n; i++) {
        if(primes[i] == false)
            continue;
        if((primes[i] == true) && (primes[n-i] == true)) {
            res.push_back(i);
            res.push_back(n-i);
            break;
        }
    }
    
    sort(res.begin(), res.end());
}

void print_res()
{
    for(auto v : res) {
        cout << v << ' ';
    }
}

int main()
{
    init();
    calc_primes();
    calc_res();
    print_res();
}