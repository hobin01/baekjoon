#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// dp[i][j] = num + dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1]
// x1, y1 ~ x2, y2까지 합
// dp[x2][y2] - (dp[x2][y1-1] + dp[x1-1][y2] - dp[x1-1][y1-1])

int n, m;
int map[1025][1025];
int dp[1025][1025]; // [1][1] ~ [x][y] 까지 합

void init()
{
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}
}

void getDP()
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dp[i][j] = map[i][j];
			dp[i][j] += dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
		}
	}
}

int getResult(int x1, int y1, int x2, int y2)
{
	return dp[x2][y2] - (dp[x2][y1 - 1] + dp[x1 - 1][y2] - dp[x1 - 1][y1 - 1]);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	getDP();
	while (m--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		cout << getResult(x1, y1, x2, y2) << '\n';
	}
}