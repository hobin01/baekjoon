#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n; // 0 제외 크기
vector<int> num; // 입력 값
int dp[100001][5][5]; // [i][j][k] : i번째 수 누를 떄 왼발 j, 오른발 k에 있음
int moving[5][5];

void init()
{
    num.push_back(0); // 처음 위치
    while(true) {
        int a;
        cin >> a;
        if(a == 0)
            break;
        num.push_back(a);
    }
    
    n = num.size();
    
    memset(dp, -1, sizeof(dp));
    memset(moving, 0, sizeof(moving));
    
    // 중앙에서 이동
    for(int i = 1; i <= 4; i++) {
        moving[0][i] = 2;
    }
    
    // 같은 자리 누름
    for(int i = 1; i <= 4; i++) {
        moving[i][i] = 1;
    }
    
    // 옆 자리 누름 
    moving[1][2] = 3;
    moving[1][4] = 3;
    moving[2][1] = 3;
    moving[2][3] = 3;
    moving[3][2] = 3;
    moving[3][4] = 3;
    moving[4][1] = 3;
    moving[4][3] = 3;
    
    // 건너 자리 누름 
    moving[1][3] = 4;
    moving[2][4] = 4;
    moving[3][1] = 4;
    moving[4][2] = 4;
}

int calc(int idx, int left, int right)
{
    // dp[i][left][right] 
    // = min(dp[i+1][next][right] + moving[left][next],
    // dp[i+1][left][next] + moving[right][next])
    // 즉 왼발로 next로 옮겼는지 오른발로 next로 옮겼는지 판단 
    
    // idx : 현재 탐색 번호 
    // left, right : 왼발, 오른발 위치 번호 
    
    // 끝까지 도달
    if(idx == n)
        return 0;
        
    // 안되는 케이스 (중앙 제외) 
    if(left != 0 && right != 0 && left == right)
        return 987654321;
    
    // dp 값 존재 
    if(dp[idx][left][right] != -1)
        return dp[idx][left][right];
    
    // 다음 수
    int next = num[idx+1];
    
    // dp 계산 
    int moving_left = calc(idx+1, left, next) + moving[right][next];
    int moving_right = calc(idx+1, next, right) + moving[left][next];
    
    int res = min(moving_left, moving_right);
    dp[idx][left][right] = res;
    return res;
}

int main()
{
    init();
    cout << calc(0, 0, 0);
}