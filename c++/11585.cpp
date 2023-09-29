#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n;
string meat;
string board;
int denominator; // 분자 체크용 

// board 2개 이어 붙혀서 kmp 진행
// 단 체크는 board 1개 범위 내에서
// 1/1 되는 경우 : n=1 인 경우 (답 0 인 거 없으므로)

void init()
{
    cin >> n;
    meat = "";
    for(int i = 0; i < n; i++) {
        char c;
        cin >> c;
        meat += c;
    }
    for(int i = 0; i < n; i++) {
        char c;
        cin >> c;
        board += c;
    }
    
    board += board;
    
    denominator = 0;
}

int gcd(int a, int b)
{
    // 기약분수라 gcd 필요
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

vector<int> getPi(string &p)
{
    // pi 배열 : pi[i] = p의 0 ~ i 부분 문자열 중 prefix == suffix 만족하는 최대 길이 
    vector<int> pi;
    pi.resize(p.size(), 0);
    int i = 0, j = 0;
    
    // 1자리 부분 문자열은 prefix 체크 제외
    for(i = 1; i < p.size(); i++) {
        while((j > 0) && (p[i] != p[j]))
            j = pi[j - 1];
            
        if(p[i] == p[j]) {
            j++;
            pi[i] = j;
        }
    }
    
    return pi;
}

void KMP(string &t, string &p)
{
    // t : 체크 당할 문자열 (가만히 있을 애)
    // p : pi 배열 이용해서 체크할 문자열 (움직일 애)
    int i = 0, j = 0;
    vector<int> pi = getPi(p);
    
    for(i = 0; i < t.size(); i++) {
        while((j > 0) && (t[i] != p[j]))
            j = pi[j - 1];
        
        if(t[i] == p[j]) {
            if(j == (p.size() - 1)) {
                // 일치하는 위치
                int idx = i - p.size() + 1;
                // 0번째부터 일치해서 n번째에서 일치하는 경우 제외 
                if(idx < n)
                    denominator++;
                j = pi[j];
            }
            else
                j++;
        }
    }
    
    // gcd 구하기
    int g = gcd(n, denominator);
    
    // 답 구하기
    cout << denominator / g << "/" << n / g;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    if(n == 1) {
        cout << "1/1";
        return 0;
    }
    KMP(board, meat);
}

