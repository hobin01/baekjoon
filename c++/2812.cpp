#include <iostream>
#include <stack>
#include <string>

using namespace std;

// 스택에 주어진 수를 앞에서부터 넣는데 
// top보다 작거나 같은 수 오면 그냥 push
// top보다 큰 수 오면 push 하는 애보다 크거나 같은 수 나올 때까지 pop
// 반복 후 pop 계속 
// pop 카운트 k 되면 종료

int n, k;
stack<char> stk;
string s;
string res;

void init()
{
    cin >> n >> k;
    cin >> s;
}

void calc()
{
    // pop 한 횟수
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(stk.empty()) {
            stk.push(s[i]);
        }
        else {
            char top = stk.top();
            if(top >= s[i]) {
                stk.push(s[i]);
            }
            else {
                while(true) {
                    // pop 할 거 없음
                    if(stk.empty())
                        break;
                    
                    // 더 이상 빼면 안 됨
                    if(cnt == k)
                        break;
                    
                    top = stk.top();
                    // 크거나 같은 경우
                    if(top >= s[i])
                        break;
                        
                    stk.pop();
                    cnt++;
                }
                
                stk.push(s[i]);
            }
        }
    }
    
    // 더 빼야 함 
    if(cnt < k) {
        int r = k - cnt;
        while(r--) {
            stk.pop();
        }
    }
    
    // 결과 구하기
    res = "";
    while(!stk.empty()) {
        res += stk.top();
        stk.pop();
    }
    
    // 결과 : res 역순
    for(int i = res.size() - 1; i >= 0; i--) {
        cout << res[i];
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    calc();
}
