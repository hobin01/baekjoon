#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string s;
string ans;

vector<int>cpp; // _ 위치 저장
vector<int>java; // 대문자 위치 저장 

void init()
{
    cin >> s;
}

bool errorCheck()
{
    // 첫 글자 대문자
    if (s[0] >= 'A' && s[0] <= 'Z')
        return true;
    // 첫 글자 _ 이거나 마지막 _ 
    if (s[0] == '_' || s[s.size() - 1] == '_')
        return true;

    // _ 위치 확인
    vector<int> idx;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '_')
            idx.push_back(i);
    }

    // _ 없는 경우
    if (idx.size() == 0)
        return false;
    // _ 1개인 경우 중간에 대문자 있나 확인
    if (idx.size() == 1) {
        string tmp1 = s.substr(0, idx[0]);
        string tmp2 = s.substr(idx[0] + 1, 100);
        for (int i = 0; i < tmp1.size(); i++) {
            if (tmp1[i] >= 'A' && tmp1[i] <= 'Z')
                return true;
        }
        for (int i = 0; i < tmp2.size(); i++) {
            if (tmp2[i] >= 'A' && tmp2[i] <= 'Z')
                return true;
        }
        // 없으면 not error
        return false;
    }

    // _ 연속 2개 이상 
    for (int i = 0; i < idx.size() - 1; i++) {
        if (idx[i] + 1 == idx[i + 1])
            return true;
    }

    // _ 사이에 대문자 존재
    string tmp;
    tmp = s.substr(0, idx[0]);
    for (int i = 0; i < tmp.size(); i++) {
        if (tmp[i] >= 'A' && tmp[i] <= 'Z')
            return true;
    }

    for (int i = 0; i < idx.size() - 1; i++) {
        int diff = idx[i + 1] - idx[i] - 1;
        tmp = s.substr(idx[i] + 1, diff);
        for (int j = 0; j < tmp.size(); j++) {
            if (tmp[j] >= 'A' && tmp[j] <= 'Z')
                return true;
        }
    }

    tmp = s.substr(idx[idx.size() - 1] + 1, 100);
    // 최대 100글자이므로 마지막까지 끊기
    for (int i = 0; i < tmp.size(); i++) {
        if (tmp[i] >= 'A' && tmp[i] <= 'Z')
            return true;
    }

    return false;
}

// _랑 대문자 위치 확인 
void indexCheck()
{
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '_')
            cpp.push_back(i);
    }

    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            java.push_back(i);
    }
}

// cpp or java check 
bool isCpp()
{
    if (cpp.size() == 0)
        return false;
    return true;
}

// 소문자만 있는 경우
bool onlyLower()
{
    if (cpp.size() == 0 && java.size() == 0)
        return true;
    return false;
}

// cpp -> java 
void cppToJava()
{
    // 첫 _까지 계산
    string tmp = s.substr(0, cpp[0]);
    ans = "";
    ans += tmp;

    // 중간 계산 
    for (int i = 0; i < cpp.size() - 1; i++) {
        int diff = cpp[i + 1] - cpp[i] - 1;
        tmp = s.substr(cpp[i] + 1, diff);
        char c = tmp[0];
        int upperDiff = (int)('A' - 'a');
        tmp[0] = c + upperDiff;
        ans += tmp;
    }

    // 마지막 _부터 마지막까지 계산 (최대 100글자)
    tmp = s.substr(cpp[cpp.size() - 1] + 1, 100);
    tmp[0] += (int)('A' - 'a');
    ans += tmp;
}

void javaToCpp()
{
    // 첫 대문자까지 계산 
    string tmp = s.substr(0, java[0]);
    ans = "";
    ans += tmp;
    ans += "_";

    // 중간 계산 
    for (int i = 0; i < java.size() - 1; i++) {
        int diff = java[i + 1] - java[i];
        tmp = s.substr(java[i], diff);
        char c = tmp[0];
        int lowerDiff = (int)('A' - 'a');
        tmp[0] = c - lowerDiff;
        ans += tmp;
        ans += "_";
    }

    // 마지막 계산 
    tmp = s.substr(java[java.size() - 1], 100);
    char c = tmp[0];
    tmp[0] = c - (int)('A' - 'a');
    ans += tmp;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();

    if (errorCheck())
        cout << "Error!";
    else {
        indexCheck();

        if (onlyLower()) {
            cout << s;
            return 0;
        }

        if (isCpp()) {
            cppToJava();
            cout << ans;
        }
        else {
            javaToCpp();
            cout << ans;
        }
    }

    return 0;
}