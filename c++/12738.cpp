#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> vec;
vector<int> lis; 
// lis[i] : 길이 i+1인 LIS의 가장 큰 수 중 가장 작은 값
// 가장 작은 값들로 저장되므로 오름차순 정렬됨됨

void init()
{
    cin >> n;
    vec.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    lis.resize(n);
}

void calc()
{
    int idx = 0;
    for(int i = 0; i < n; i++) {
        int pos = lower_bound(lis.begin(), lis.begin() + idx, vec[i]) - lis.begin();
        lis[pos] = vec[i];
        if(pos == idx) {
            idx++;
        }
    }
    
    cout << idx;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    calc();
    
}