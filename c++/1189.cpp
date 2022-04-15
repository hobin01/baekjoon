#include <iostream>
#include <cstring>

using namespace std;

int r, c, k;
char map[6][6];
bool check[6][6];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
pair<int, int>start;
pair<int, int>last;
int result;

void init()
{
	cin >> r >> c >> k;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> map[i][j];
		}
	}
	memset(check, false, sizeof(check));
	start = { r - 1,0 };
	last = { 0, c - 1 };
	result = 0;

}

void dfs(int y, int x, int cnt)
{
	if (y < 0 || y >= r || x < 0 || x >= c)
		return;
	if (check[y][x] == true)
		return;
	if (map[y][x] == 'T')
		return;
	if (y == last.first && x == last.second) {
		if (cnt == k) {
			result++;
			return;
		}
		else
			return;
	}

	check[y][x] = true;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= r || nx < 0 || nx >= c)
			continue;
		if (check[ny][nx] == true)
			continue;
		dfs(ny, nx, cnt + 1);
		check[ny][nx] = false;
	}
	return;
}

int main()
{
	init();

	dfs(start.first, start.second, 1);

	cout << result;
}