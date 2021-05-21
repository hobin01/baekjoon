#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

int r, c;
char map[10001][501];
bool visited[10001][501]; // 방문 여부, 빌딩은 항상 방문으로 처리
int dy[3] = { -1,0,1 };
int dx[3] = { 1,1,1 };
int result = 0;

void make_map()
{
	cin >> r >> c;
	for (int i = 1; i <= r; i++) {
		string s;
		cin >> s;
		for (int j = 1; j <= s.size(); j++) {
			map[i][j] = s[j - 1];
			visited[i][j] = false;
			if (s[j - 1] == 'x') {
				visited[i][j] = true;
			}
		}
	}
}

// 1,1 부터 최대한 대각선 위로 그 다음에 우로 그 다음에 대각선 아래로 진행
// 리턴 값이 false면 더 이상 갈 수 없음
// x 위치 c일때만 경로가 된 것
bool dfs(int y, int x)
{
	visited[y][x] = true;

	if (x == c) {
		result++;
		return true;
	}

	for (int i = 0; i < 3; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 1 || ny > r || nx < 1 || nx > c)
			continue;

		if (map[ny][nx] == 'x')
			continue;

		if (visited[ny][nx] == false && map[ny][nx] == '.') {
			if(dfs(ny, nx))
				return true;
		}
	}

	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_map();

	for (int i = 1; i <= r; i++) {
		visited[i][1] = true;
		dfs(i, 1);
	}

	cout << result;
}