#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define mod 1000000000
#define check 1023
// 9876543210의 여부 : 1111111111 = 1023 (바이너리로)

int n; // n <= 100
int result;
int dp[101][10][check + 1]; 

// dp[i][j][k] : i번째가 j인데 k만큼 체크된 경우의 수
// 첫 자리 0 안 되므로 첫 번째 1 ~ 9의 dp값 1
// k | (1 << j)로 i번째에 j라는 수 들어갔고 기존에 k만큼 체크되었음
// i-1 번째에 j-1, j+1이라는 수 들어올 수 있고, 이 때 k만큼 체크되었음 

// i번째가 0이면 i-1번째는 1밖에 안 됨
// j = 0 : dp[i][j][k | (1 << j)] += dp[i - 1][1][k] % mod
// i번째가 9이면 i-1번째는 8밖에 안 됨
// j = 9 : dp[i][j][k | (1 << j)] += dp[i - 1][8][k] % mod
// 나머지는 +-1 가능
// else : dp[i][j][k | (1 << j)] += (dp[i - 1][j - 1][k] + dp[i - 1][j + 1][k]) % mod
// 최종 합 계산 시 dp[n][...][check] 합하면 됨

// dp 계산 시 10억 미만이고, 10억 + 10억 => int로 가능

void init()
{
  cin >> n;
  memset(dp, 0, sizeof(dp));  

  // 1번째 수 0 X
  for(int i = 1; i <= 9; i++) {
    dp[1][i][1 << i] = 1;
  }

  result = 0;
}

void getDP()
{
  int chk = 0;
  for(int i = 2; i <= n; i++) {
    for(int j = 0; j <= 9; j++) {
      for(int k = 0; k <= check; k++) {
        chk = k | (1 << j);
        if(j == 0){
          dp[i][j][chk] += dp[i - 1][1][k];
          dp[i][j][chk] %= mod;
        }
        else if(j == 9) {
          dp[i][j][chk] += dp[i - 1][8][k];
          dp[i][j][chk] %= mod;
        }
        else {
          dp[i][j][chk] += dp[i - 1][j - 1][k];
          dp[i][j][chk] %= mod;
          dp[i][j][chk] += dp[i - 1][j + 1][k];
          dp[i][j][chk] %= mod;
        }
      }
    }
  }
}

void getResult()
{
  for(int i = 0; i <= 9; i++) {
    result += dp[n][i][check];
    result %= mod;
  }

  cout << result;
}

int main() {
  init();
  getDP();
  getResult();
}