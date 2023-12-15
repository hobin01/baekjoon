#include <iostream>
#include <vector>

using namespace std;

// 패턴은 *a + b 
// n=1 이면 무조건 A 
// n=2 인 경우, x1=x2면 답 x1, 아니면 A
// n>=3 인 경우 
// x1*a+b=x2, x2*a+b=x3 => 해 (a,b) 유일
// a*(x2-x1)=(x3-x2)
// x2=x1 인 경우, 모든 수 같은 지 체크 
// 맞으면 답 x1, 아니면 B 
// x2!=x1, x3=x2인 경우, 
// x2=x3=... 이면 a=0, b=x2 이므로 답 x2 
// 다른 거 하나라도 있으면 B
// 나머지 경우 
// a 정수 아니면 B 
// a 정수 맞으면 b 계산, 모든 수에 대해 적용 후 맞으면 답 계산
// 아니면 B

int n;
vector<int> v;

void init()
{
    cin >> n;
    v.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
}

void calc()
{
    if(n == 1) {
        cout << "A";
        return;
    }
    
    if(n == 2) {
        if(v[0] == v[1]) {
            cout << v[0];
            return;
        }
        else {
            cout << "A";
            return;
        }
    }
    
    if(n >= 3) {
        // y1 = x2-x1
        // y2 = x3-x2
        int y1 = v[1] - v[0];
        int y2 = v[2] - v[1];
        
        // x2=x1 
        if(y1 == 0) {
            for(int i = 1; i < n; i++) {
                // 다른 거 있는 경우 
                if(v[0] != v[i]) {
                    cout << "B";
                    return;
                }
            }
            
            cout << v[0];
            return;
        }
        
        // x3=x2
        if(y2 == 0) {
            // 다른 거 하나라도 있는 경우
            for(int i = 2; i < n; i++) {
                if(v[1] != v[i]) {
                    cout << "B";
                    return;
                }
            }
            
            cout << v[1];
            return;
        }
        
        int a = y2 / y1;
        
        // a 정수 아닌 경우 
        if((a * y1) != y2) {
            cout << "B";
            return;
        }
        
        int b = v[1] - a * v[0];
        for(int i = 1; i < n; i++) {
            // 다른 거 있는 경우 
            if(v[i] != (a * v[i-1] + b)) {
                cout << "B";
                return;
            }
        }
        
        cout << v[n-1] * a + b; 
        return;
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