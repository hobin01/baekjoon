#include <iostream>

using namespace std;

typedef long long ll;
ll n;
ll dp[1000001];
// dp[n] = (n-1) * (dp[n-2] + dp[n-1])
ll mod = 1000000000;

void init()
{
  cin >> n;
}

void calc()
{
  dp[0] = 0;
  dp[1] = 0;
  dp[2] = 1;
  
  for(ll i = 3; i <= n; i++) {
    dp[i] = ((i - 1) * ((dp[i - 2] + dp[i - 1]) % mod)) % mod;
  }

  cout << dp[n];
}

int main() {
  init();
  calc();
}