#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;
vector<int> vec;
int res;

void init()
{
    cin >> n;
    vec.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    
    sort(vec.begin(), vec.end());
}

void init_res()
{
    // 2번째가 가운데인 케이스 
    // (1,2,3),(4,5),(6,7),...
    
    res = vec[2] - vec[0];
    for(int i = 3; i < (n-1); i+=2) {
        res += (vec[i+1] - vec[i]);
    }
}

void calc()
{
    // 3개 짜리는 어짜피 가운데 무시 
    // 2번째 값부터 3개씩 묶어서 체킹 (짝수번째만 가운데 오도록)
    
    int tmp = res;
    
    for(int i = 3; i < (n-1); i+=2) {
        // i : 가운데 올 index 
        tmp += (vec[i-2] - vec[i-1]) + (vec[i] - vec[i-1]);
        res = min(res, tmp);    
    }
    
    cout << res;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    init_res();
    calc();
}