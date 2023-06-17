#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> v;
int result;

void init()
{
    cin >> n;
    v.resize(n + 2);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    result = 0;
}

void calc()
{
    int m;
    for(int i = 0; i < n; i++) {
        if(v[i] == 0)
            continue;
        if(v[i+1] > v[i+2]) {
            // i, i+1 번에서 사는 경우
            m = min(v[i], v[i+1] - v[i+2]);
            result += (5 * m);
            v[i] -= m;
            v[i+1] -= m;
            
            // i+2번까지 연속으로 살 수 있는 경우
            m = min(v[i], min(v[i+1], v[i+2]));
            result += (7 * m);
            v[i] -= m;
            v[i+1] -= m;
            v[i+2] -= m;
            
            // i번에서 남은 거 사기
            result += (3 * v[i]);
            v[i] = 0;
        }
        
        else {
            // i+2번까지 연속으로 살 수 있는 경우 
            m = min(v[i], v[i+1]);
            result += (7 * m);
            v[i] -= m;
            v[i+1] -= m;
            v[i+2] -= m;
            
            // i번 남은 거 사기 
            result += (3 * v[i]);
            v[i] = 0;
        }
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    calc();
    cout << result;
}