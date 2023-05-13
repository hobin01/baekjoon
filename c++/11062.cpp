#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int T;
int N;
vector<int> cards;
int dp[1001][1001]; 
// dp[i][j] : i ~ j번째 카드 있을 때 얻는 최대 값

void init()
{
    cin >> N;
    cards.clear();
    cards.resize(N);
    for(int i = 0; i < N; i++) {
        cin >> cards[i];
    }
    memset(dp, 0, sizeof(dp));
}

int game(int left, int right, int idx)
{
    // 안 되는 경우
    if(left > right)
        return 0;
        
    // 이미 계산된 경우
    if(dp[left][right] != 0)
        return dp[left][right];
    
    // 근우 차례
    // 뽑은 애들 합 최대로
    if (idx % 2 == 0) 
        dp[left][right] = 
            max(
                cards[left] + game(left + 1, right, idx + 1), 
                cards[right] + game(left, right - 1, idx + 1)
                );
    // 명우 차례
    // 뽑은 애들 합 최소로
    else 
        dp[left][right] = 
            min(
                game(left + 1, right, idx + 1), 
                game(left, right - 1, idx + 1)
                );
    
    return dp[left][right];
}

int main()
{
    cin >> T;
    while(T--) {
        init();
        game(0, N - 1, 0);
        cout << dp[0][N - 1] << '\n';
    }
}