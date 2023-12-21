#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 최대 최소만 보면 됨
// 최대 최소가 될 수 있는 케이스는 (연속 2자리, 구간 길이 1 제외)
// 길이 n+2일 때 nC0 + nC1 + .. + nCn = 2^n (n>=1, 짝수)
// 따라서 xor 해봤자 0 나옴 
// ex. 정렬된 상태에서 1 2 3 4 5 라면 
// (1,5) 최소, 최대가 되는 건 3C0+3C1+3C2+3C3 케이스 
// 실제 배열 상에서도 위 케이스가 그대로 있음 (섞여 있을 뿐)
// 그러므로 1자리 짜리 애들 따로 계산, 정렬하고 연속 2자리 애들 따로 계산

long long n;
vector<long long> vec;
long long res;

void init()
{
    cin >> n;
    vec.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    res = 0;
}

void single()
{
    // 길이 1짜리 
    for(auto v : vec) {
        res ^= (v * v);
    }
}

void sequential()
{
    // 정렬 후 길이 2 연속인 애들
    sort(vec.begin(), vec.end());
    for(int i = 0; i < (n-1); i++) {
        res ^= (vec[i] * vec[i+1]);
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    single();
    sequential();
    cout << res;
}