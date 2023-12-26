#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

int n;
int nums[100001]; // 원래 숫자들 
map<int, int> m; // left ~ right 까지 등장횟수 카운트용 
long long result;

void init()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
    }
    m[nums[1]] = 1; // 투 포인터 처음 포인터용 
    result = 0;
}

void calc()
{
    int left, right;
    left = 1;
    right = 1;
    
    while(1) {
        while(right < n) {
            // right 위치 값 기존 거에 포함 안 될 때까지 카운트 
            if(m[nums[right+1]] != 0)
                break;
            right++;
            m[nums[right]]++;
        }
        
        // 끝나는 케이스 
        if((left > n) || (right > n))
            break;
        
        // left 이동 및 경우의 수 적용 
        result += (long long)(right - left + 1);
        // 원래 left 위치 거 제거 
        m[nums[left]]--;
        left++;
    }
    
    cout << result;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    calc();
}