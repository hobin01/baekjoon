#include <iostream>
#include <string>
#include <cstring>

using namespace std;

string S;
int q, l, r;
char c;

int dp[200000][26]; // 알파벳 26개

void init()
{
    cin >> S;
    cin >> q;
    memset(dp, 0, sizeof(dp));
}

void calc()
{
    dp[0][S[0] - 'a'] = 1;
    
    for(int i = 1; i < S.size(); i++) {
        int idx = S[i] - 'a'; // 소문자로만 구성
        for(int j = 0; j < 26; j++) {
            dp[i][j] = dp[i - 1][j];
        }
        dp[i][idx] = dp[i - 1][idx] + 1;
    }
}

void query()
{
    cin >> c >> l >> r;
    
    // case1 : S[l] != c && S[r] != c || S[l] != c && S[r] == c 
    if(S[l] != c) {
        cout << dp[r][c - 'a'] - dp[l][c - 'a'] << '\n';
    }
    
    // case2 : S[l] == c && S[r] != c || S[l] == c && S[r] == c 
    else {
        cout << dp[r][c - 'a'] - dp[l][c - 'a'] + 1 << '\n';
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    calc();
    while(q--) {
        query();
    }
}