#include <iostream>

using namespace std;

int n;
long long mod = 1000000;

long long dpAsc[100][100];
// dp1[i][j] : 작은 거 i 개, 큰 거 j 개 남았을 때 현재 고른 수보다 큰 수 고르는 경우의 수
long long dpDsc[100][100];
// dp1[i][j] : 작은 거 i 개, 큰 거 j 개 남았을 때 현재 고른 수보다 작은 수 고르는 경우의 수

long long result;

int calc_asc(int less, int greater);
int calc_dsc(int less, int greater);

void init()
{
    cin >> n;
    
    // 단순 계산 가능한 케이스 
    if(n == 1) {
        cout << 1;
        exit(0);
    }
    if(n == 2) {
        cout << 2;
        exit(0);
    }
    if(n == 3) {
        cout << 4;
        exit(0);
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            dpAsc[i][j] = -1;
            dpDsc[i][j] = -1;
        }
    }
    
    // 미리 계산 가능한 케이스
    dpAsc[0][1] = 1;
    dpAsc[1][1] = 1;
    dpDsc[1][0] = 1;
    dpDsc[1][1] = 1;
    
    result = 0;
}

int calc_asc(int less, int greater)
{
    // 현재까지 탐색한 것 중 작은 거 less 개, 큰 거 greater 개 남았을 때
    // 더 큰 거 고르는 경우의 수 계산
    
    // 이미 동일한 케이스 계산 
    if(dpAsc[less][greater] != -1)
        return dpAsc[less][greater];
    
    // 더 큰 거 못 고름 
    if(greater == 0)
        return 0;
    
    long long res = 0;
    // 큰 것 중 i 번째 것 골랐을 때 내려가는 방향에서의 경우의 수만큼
    for(int i = 0; i < greater; i++) {
        res += calc_dsc(less + i, greater - (i + 1));
        res %= mod;
    }
    
    dpAsc[less][greater] = res;
    return res;
}

int calc_dsc(int less, int greater)
{
    // 마찬가지로 현재 탐색 기준으로 더 작은 거 고르는 경우의 수 
    
    if(dpDsc[less][greater] != -1)
        return dpDsc[less][greater];
    
    if(less == 0)
        return 0;
    
    long long res = 0;
    for(int i = 0; i < less; i++) {
        res += calc_asc(i, greater + less - (i + 1));
        res %= mod;
    }
    
    dpDsc[less][greater] = res;
    return res;
}

void game()
{
    // 시작 오름, 내림 순 각각 계산 
    for(int i = 0; i < n; i++) {
        result += calc_asc(i, n - (i + 1));
        result %= mod;
        result += calc_dsc(i, n - (i + 1));
        result %= mod;
    }
    
    cout << result;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    init();
    game();
}