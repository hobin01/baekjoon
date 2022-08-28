#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <set>
#include <cstring>
#include <algorithm>

using namespace std;

string n;
int k;
string ans;

void init()
{
    cin >> n;
    cin >> k;
    ans = "";
}

void bfs()
{
    // k번 진행하면서
    // 스왑시킨 것들 전부 큐에 넣기
    // set에 존재하면 동일한 케이스이므로 패스 
    set<string> check;
    set<string>::iterator iter;
    
    queue<string>q;
    
    q.push(n);
    int start = 0;
    int last = n.size() - 1;
    
    for(int i = 0; i < k; i++) {
        
        check.clear();
        
        // k번 진행한 거 구분하기 위해 
        // 이전 큐 사이즈만큼만 진행 
        int q_size = q.size();
        for(int j = 0; j < q_size; j++) {
            string tmp = q.front();
            q.pop();
            
            for(int u = start; u < last; u++) {
                for(int v = u + 1; v <= last; v++) {
                    string swap_tmp = tmp;
                    swap(swap_tmp[u], swap_tmp[v]);
                    
                    iter = check.find(swap_tmp);
                    // 스왑한 거 set에 없음 
                    if(iter == check.end()) {
                        check.insert(swap_tmp);
                        q.push(swap_tmp);
                    }
                }
            }
        }
        
        // k번 진행 시 최대값 구하기 
        if(i == (k - 1)) {
            ans = q.front();
            while(!q.empty()) {
                string tmp = q.front();
                q.pop();
                if(tmp > ans)
                    ans = tmp;
            }
        }
    }
    
    cout << ans;
}

bool fail()
{
    // 불가능한 경우
    // 1자리는 스왑 불가 
    if(n.size() == 1)
        return true;
    // 2자리인데 1의 자리가 0이어도 스왑 불가 
    if(n.size() == 2 && n[0] != '0' && n[1] == '0')
        return true;
    // 나머지는 가능 
    return false;
}

int main()
{
    init();
    
    if(fail())
        cout << -1;
    else
        bfs();
}