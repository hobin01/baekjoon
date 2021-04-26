#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,1,-1 };
int map[501][501];
int dp[501][501];
int n;

void make_map()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			dp[i][j] = 0;
		}
	}
}

int dfs(int x, int y)
{
	if (dp[y][x] != 0)
		return dp[y][x];
	
	dp[y][x] = 1;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny >= 0 && ny < n && nx >= 0 && nx < n) {
			if (map[y][x] < map[ny][nx]) {
				dp[y][x] = max(dp[y][x], dfs(nx, ny) + 1);
			}
		}
	}
	return dp[y][x];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_map();
	int result = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result = max(result, dfs(j, i));
		}
	}
	cout << result;
}