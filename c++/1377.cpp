#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 정렬 전, 후 비교해서 index 차의 max + 1 
// 차이 : 정렬 후 - 정렬 전 기준 
// 음수이면 원래 있던 위치보다 뒤로 간 케이스
// 양수이면 원래 있던 위치보다 앞으로 간 케이스 
// 버블 소트하면 큰거는 자연스럽게 뒤로 가므로
// 앞으로 간거만 고려하면 됨 

int N;
vector<pair<int, int>> vec;

void init()
{
    cin >> N;
    vec.resize(N);
    for(int i = 0; i < N; i++) {
        int num;
        cin >> num;
        vec[i].first = num;
        vec[i].second = i;
    }
}

void calc()
{
    vector<pair<int, int>> vec2 = vec;
    sort(vec2.begin(), vec2.end());
    
    // vec : 정렬 전, vec2 : 정렬 후 
    int res = 0;
    for(int i = 0; i < N; i++) {
        int diff = vec2[i].second - vec[i].second;
        if(res < diff) {
            res = diff;
        }
    }
    
    cout << res + 1;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    calc();
}