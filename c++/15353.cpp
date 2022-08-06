#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    string s1, s2;
    cin >> s1 >> s2;
    
    int s1_len = s1.size();
    int s2_len = s2.size();
    int s_len = max(s1_len, s2_len);
    
    string s(s_len + 1, '0');
        
    if(s1_len > s2_len) {
        string tmp(s1_len - s2_len, '0');
        tmp += s2;
        s2 = tmp;
    }
    else if(s1_len < s2_len) {
        string tmp(s2_len - s1_len, '0');
        tmp += s1;
        s1 = tmp;
    }
    
    int carry = 0;
    for(int i = s_len - 1; i >= 0; i--) {
        int sum = (s1[i] - '0') + (s2[i] - '0') + carry;
        carry = sum / 10;
        sum %= 10;
        s[i + 1] = sum + '0';
    }
    s[0] = carry + '0';
    
    if(s[0] == '0')
        s = s.substr(1);
    
    cout << s;
}