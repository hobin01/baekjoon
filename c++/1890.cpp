#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

typedef unsigned long long ull;

int main()
{
	int n;
	cin >> n;

	int board[101][101];
	ull dp[101][101];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> board[i][j];

	for (int i = 0; i < n; i++)
		memset(dp[i], 0, sizeof(ull) * n);

	dp[0][0] = 1;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (dp[i][j] == 0)
				continue;
			if ((i == (n - 1)) && (j == (n - 1)))
				continue;
			int num = board[i][j];
			int y = num + i;
			int x = num + j;

			if (y < n)
				dp[y][j] += dp[i][j];
			if (x < n)
				dp[i][x] += dp[i][j];
		}
	}

	cout << dp[n - 1][n - 1];
}