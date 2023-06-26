#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, k;
vector<int> vec;
vector<bool> check;

void init()
{
    cin >> n >> m >> k;
    
    vec.resize(m * k);
    check.resize(n + 1, false);
    check[0] = true;
    
    for(int i = 1; i <= m; i++) {
        vec[i * k - 1] = i;
        check[i] = true;
    }
}

void calc()
{
    for(int i = n; i > 0; i--) {
        if(check[i])
            continue;
        
        int chk = 0;
        int idx = -1;
        for(int j = m * k - 1; j >= 0; j--) {
            if(vec[j] == 0 && chk == 0) {
                chk = 1;
            }
            
            else if(vec[j] != 0 && chk == 1) {
                idx = j + 1;
                break;
            }
        }
        
        // idx가 맨 앞에 0 가리키는 경우 
        if(chk == 1 && idx == -1) {
            idx = 0;
        }
        
        // 더 이상 수 넣기 불가능한 경우
        else if(idx == -1) {
            break;
        }
        
        for(int j = 0; j < k - 1; j++) {
            if(check[i - j] == false) {
                vec[idx + j] = i - j;
                check[i - j] = true;
            }
        }
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    // 일단 1 ~ m 으로 k 간격으로 가장 긴 증가하는 수열 생성
    // 그리고 나머지 칸에 큰 수 순으로 대입하여 가장 긴 감소하는 수열 길이 k 되도록
    
    init();
    
    // 비둘기집 원리에 의해 안 되는 경우 
    if(m + k - 1 > n || n > m * k) {
        cout << -1;
        return 0;
    }
    
    // k=1 인 경우 
    if(k == 1 && n == m) {
        for(int i = 1; i <= n; i++) {
            cout << i << ' ';
        }
        return 0;
    }
    
    calc();
    
    for(auto v : vec) {
        if(v != 0) {
            cout << v << ' ';
        }
    }
    
    return 0;
}