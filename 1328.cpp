#include <iostream>

using namespace std;

int n, l, r;
long long dp[101][101][101] = { 0 };

#define mod 1000000007

void init()
{
	cin >> n >> l >> r;

	// base
	// 0개 가 l, r에 들어올 수는 없음
	// dp[n][l][r] = 0 , where, n = 0 or l = 0 or r = 0
	// dp[1][1][1] = 1, dp[2][1][2] = 1, dp[2][2][1] = 1
	// 나머지는 계산
	// dp[n+1][l][r] = 
	// dp[n][l-1][r] (가장 작은 거 맨 왼쪽에 세우는 경우) + 
	// dp[n][l][r-1] (가장 작은 거 맨 오른쪽에 세우는 경우) + 
	// dp[n][l][r] * (n-1) (가장 작은 거 n개 블록의 사이에 끼워 넣는 경우)

	dp[1][1][1] = 1;
	dp[2][2][1] = 1;
	dp[2][1][2] = 1;
}

int main()
{
	init();

	for (int i = 2; i < n; i++) { // n+1 개 블록으로 계산해서 얘만 i < n 까지
		for (int j = 1; j <= l; j++) {
			for (int k = 1; k <= r; k++) {
				dp[i + 1][j][k] = dp[i][j - 1][k] + dp[i][j][k - 1] + dp[i][j][k] * (i - 1);
				dp[i + 1][j][k] %= mod;
			}
		}
	}

	cout << dp[n][l][r];
}