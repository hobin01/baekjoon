#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int map[101][101];
string dp[101][101];

void init()
{
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> map[i][j];
            dp[i][j] = "";
        }
    }
}

string bigSum(string s1, string s2) 
{
    int size = max(s1.size(), s2.size()) + 1;
    string result(size, '0');
    
    if(s1.size() > s2.size()) {
        int diff = s1.size() - s2.size();
        string tmp(diff, '0');
        tmp += s2;
        s2 = tmp;
    }
    else if(s1.size() < s2.size()) {
        int diff = s2.size() - s1.size();
        string tmp(diff, '0');
        tmp += s1;
        s1 = tmp;
    }
    
    int carry = 0;
    for(int i = s1.size() - 1; i >= 0; i--) {
        int sum = (s1[i] - '0') + (s2[i] - '0') + carry;
        carry = sum / 10;
        sum %= 10;
        result[i + 1] = sum + '0';
    }
    result[0] = carry + '0';
    
    if(result[0] == '0')
        return result.substr(1);
    else 
        return result;
}

string calc(int y, int x)
{
    if(y == (n - 1) && x == (n - 1))
        return "1";
    if(y >= n || x >= n || y < 0 || x < 0)
        return "0";
    if(map[y][x] == 0)
        return "0";
    if(dp[y][x] != "")
        return dp[y][x];
    
    int ny = y + map[y][x];
    int nx = x + map[y][x];
    
    dp[y][x] = bigSum(calc(ny, x), calc(y, nx));
    return dp[y][x];
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    
    calc(0, 0);
    cout << dp[0][0];
}