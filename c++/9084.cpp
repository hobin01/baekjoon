#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int T;
int N, M;
int coin[21]; // i번째 동전 값
int dp[10001]; // i 만드는데 필요한 경우의 수

void init()
{
  memset(coin, 0, sizeof(coin));
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;

  cin >> N;
  for(int i = 1; i <= N; i++) {
    cin >> coin[i];
  }
  cin >> M;
}

void calc()
{
  for(int i = 1; i <= N; i++) {
    int c = coin[i];
    for(int j = c; j <= M; j++) {
      int tmp = dp[j - c];
      dp[j] += tmp;
    }
  }

  cout << dp[M] << '\n';
}

int main() {
  cin >> T;
  while(T--) {
    init();
    calc();
  }
}