#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int n;
vector<string> vec;

void init()
{
    cin >> n;
    vec.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> vec[i];
    }
}

bool compare(const string &s1, const string &s2)
{
    // 첫 자리 다르면 내림차순으로
    // 첫 자리 같고 글자 수 다르면 붙혀보고 비교
    
    // 앞 자리 다른 경우
    if(s1[0] != s2[0]) {
        return s1[0] > s2[0];
    }
    else {
        if(s1.size() == s2.size()) {
            // 길이 같은 경우
            return s1 > s2;        
        }
        else {
            // 길이 다르면 붙혀보고 비교
            string tmp1 = s1 + s2;
            string tmp2 = s2 + s1;
            return tmp1 > tmp2;
        }
    }
}

void calc()
{
    sort(vec.begin(), vec.end(), compare);
    
    // 전부 0인 경우
    bool chk = false;
    for(auto v : vec) {
        if(v != "0") {
            chk = true;
            break;
        }
    }
    
    if(chk == false) {
        cout << 0;
        return;
    }
    
    for(auto v : vec) {
        cout << v;
    }
    return;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    calc();
}