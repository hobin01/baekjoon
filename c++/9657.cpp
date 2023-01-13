#include <iostream>
#include <cstring>

using namespace std;

int n;
int dp[1001];

// dp[n-1] + dp[n-3] + dp[n-4] == 3 ? dp[n] = 1 : dp[n] = 0
// 1 : SK, 0 : CY
int main()
{
  cin >> n;
  memset(dp, 0, sizeof(dp));
  dp[1] = 1;
  dp[2] = 0;
  dp[3] = 1;
  dp[4] = 1;

  for(int i = 5; i <= 1000; i++) {
    dp[i] = dp[i - 1] + dp[i - 3] + dp[i - 4] == 3 ? 0 : 1;
  }

  dp[n] == 1 ? cout << "SK" : cout << "CY";
}