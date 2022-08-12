#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

string s1, s2;
int result = 0;
int dp[4001][4001]; // dp[i][j] = dp[i-1][j-1] + 1 
// dp[i][j] : s1의 i번째랑 s2의 j번째가 일치할 때 최대 길이 

void init()
{
    cin >> s1 >> s2;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    
    memset(dp, 0, sizeof(dp));   
    
    for(int i = 0; i < s1.size(); i++) {
        if(s1[i] == s2[0]){
            dp[i][0] = 1;
            result = 1;
        }
    }
    
    for(int j = 0; j < s2.size(); j++) {
        if(s2[j] == s1[0]) {
            dp[0][j] = 1;
            result = 1;
        }
    }
    
    for(int i = 1; i < s1.size(); i++) {
        for(int j = 1; j < s2.size(); j++) {
            if(s1[i] == s2[j]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                result = max(result, dp[i][j]);
            }
        }
    }
    
    cout << result;
}