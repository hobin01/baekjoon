#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <string>

using namespace std;

int n, m;
string s;
bool map[183][183];
int dist[183][183];

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

void init()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> s;
		for (int j = 0; j < m; j++) {
			dist[i][j] = -1;
			map[i][j] = (s[j] == '1');
			if (map[i][j])
				dist[i][j] = 0;
		}
		s.clear();
	}
}

void bfs()
{
	queue<pair<int, int>> q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j])
				q.push({ i, j });
		}
	}

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny < 0 || nx < 0 || ny >= n || nx >= m)
				continue;
			if (dist[ny][nx] == -1) {
				dist[ny][nx] = dist[y][x] + 1;
				q.push({ ny, nx });
			}
		}
	}
}

void print_dist()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << dist[i][j] << ' ';
		}
		cout << '\n';
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	init();
	bfs();
	print_dist();
}