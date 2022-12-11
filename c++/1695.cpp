#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n;
int arr[5001];
int dp[5001][5001];

// dp[i][j] : i~j 인 부분 배열에서
// 필요한 최소 개수
// arr[i] = arr[j] : dp[i][j] = dp[i+1][j-1]
// else : dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1

void init()
{
  cin >> n;
  memset(arr, 0, sizeof(arr));
  memset(dp, 0, sizeof(dp));
  
  for(int i = 0; i < n; i++) {
    cin >> arr[i];
  }
}

int calc(int i, int j)
{
  // 계산 완료
  if(dp[i][j] != 0)
    return dp[i][j];

  // 펠린드롬 필요 없는 경우
  // 에러 처리 겸용
  if(i >= j)
    return 0;
  
  if(arr[i] == arr[j]) {
    dp[i][j] = calc(i+1, j-1);
  }
  else {
    dp[i][j] = min(calc(i+1, j), calc(i, j-1)) + 1;
  }

  return dp[i][j];
}

int main() 
{
  init();
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      calc(i, j);
    }
  }

  cout << dp[0][n - 1];
}