#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m, k;
char arr[101][101];
string s;
int slen;

int dp[101][101][81];
// dp[a][b][c] = d : (a,b)에 존재하는 문자가 c번째 문자일 때 가능한 경우의 수 = d
// (a,b) 위치 재탐색 시 c번째 문자일 때 가능한 경우가 d개이므로 이를 재탐색하고자 하는 경로에 더하면 됨
// 경로는 dfs로 탐색

vector<pair<int, int>> start; // 시작점 위치
int dy[4] = { 0,0,-1,1 };
int dx[4] = { 1,-1,0,0 };
vector<pair<int, int>> loc; // 움직일 수 있는 위치

void init()
{
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}
	cin >> s;
	slen = s.size();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] == s[0])
				start.push_back({ i, j });
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= k; j++) {
			pair<int, int> p = { dy[i], dx[i] };
			p = { p.first * j, p.second * j };
			loc.push_back(p);
		}
	}

	memset(dp, -1, sizeof(dp));
}

int dfs(int r, int c, int idx)
{
	if (dp[r][c][idx] != -1)
		return dp[r][c][idx]; // 이전에 찾은 경로 있음

	if (idx + 1 == slen)
		return 1; // 경로 하나 찾음

	dp[r][c][idx] = 0;

	for (auto jump : loc) {
		int nr = r + jump.first;
		int nc = c + jump.second;

		if (nr < 0 || nr >= n || nc < 0 || nc >= m)
			continue;

		if (arr[nr][nc] == s[idx + 1]) {
			dp[r][c][idx] += dfs(nr, nc, idx + 1);
		}
	}

	return dp[r][c][idx];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	int res = 0;
	for (auto st : start) {
		res += dfs(st.first, st.second, 0);
	}

	cout << res;
}