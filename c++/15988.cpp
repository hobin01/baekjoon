#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
// n 만들기
// 1,2,3 밖에 없으므로
// n-1 + 1, n-2 + 2, n-3 + 3 이랑 동일

int T;
int n;
long long dp[1000001];
vector<int>test;
long long mod = 1000000009;

void init()
{
  cin >> T;
  while(T--) {
    cin >> n;
    test.push_back(n);
  }
}

void calc()
{
  dp[1] = 1;
  dp[2] = 2;
  dp[3] = 4;

  for(int i = 4; i <= 1000000; i++) {
    dp[i] = (dp[i - 1] + dp[i - 2] + dp[i - 3]) % mod;
  }
}

int main()
{
  init();
  calc();

  for(auto t : test) {
    cout << dp[t] << '\n';
  }
}