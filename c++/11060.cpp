#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int>num;
vector<int>dp;

void init()
{
    cin >> n;
    for(int i = 0; i < n; i++) {
        int A;
        cin >> A;
        num.push_back(A);
        dp.push_back(987654321);
    }
    dp[0] = 0;
}

void jump(int idx)
{
    if(idx >= n)
        return;
        
    int jmp = num[idx];
    int cnt = dp[idx];
    
    if(jmp == 0)
        return;
    
    for(int i = idx + jmp; i > idx; i--) {
        if(i >= n)
            continue;
        dp[i] = min(dp[i], cnt + 1);
    }
}

int main()
{
    init();
    
    for(int i = 0; i < (n - 1); i++) {
        jump(i);
    }
    
    if(dp[n - 1] == 987654321)
        cout << -1;
    else 
        cout << dp[n - 1];
}