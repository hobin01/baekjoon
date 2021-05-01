#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

int n;
int map[17][17];
int result = 0;

void init()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}
}

void bfs()
{
	// 큐 : 방향, {파이프 끝의 좌표}, 방향 : 1,2,3 순으로 가로 세로 대각선
	queue<pair<int,pair<int, int>> >q;
	q.push({ 1,{ 1,2 } });

	while (!q.empty()) {
		int dir = q.front().first;
		int y = q.front().second.first;
		int x = q.front().second.second;

		if (y == n && x == n)
			result++;

		q.pop();

		if (dir == 1) {
			int ny, nx, ndir;

			// 가로로 이동
			ny = y;
			nx = x + 1;
			ndir = 1;

			if (ny > 0 && ny <= n && nx > 0 && nx <= n) {
				if (map[ny][nx] == 0) {
					q.push({ ndir, {ny, nx} });
				}
			}

			// 대각선 이동
			ny = y + 1;
			nx = x + 1;
			ndir = 3;


			if (ny > 0 && ny <= n && nx > 0 && nx <= n) {
				if (map[ny][nx] == 0 && map[ny][nx - 1] == 0 && map[ny - 1][nx] == 0){
					q.push({ ndir, {ny,nx} });
				}
			}
		}

		if (dir == 2) {
			int ny, nx, ndir;

			// 세로로 이동
			ny = y + 1;
			nx = x;
			ndir = 2;

			if (ny > 0 && ny <= n && nx > 0 && nx <= n) {
				if (map[ny][nx] == 0) {
					q.push({ ndir, {ny, nx} });
				}
			}

			// 대각선 이동
			ny = y + 1;
			nx = x + 1;
			ndir = 3;

			if (ny > 0 && ny <= n && nx > 0 && nx <= n) {
				if (map[ny][nx] == 0 && map[ny][nx - 1] == 0 && map[ny - 1][nx] == 0) {
					q.push({ ndir,{ny,nx} });
				}
			}
		}

		if (dir == 3) {
			int ny, nx, ndir;

			// 가로로 이동
			ny = y;
			nx = x + 1;
			ndir = 1;

			if (ny > 0 && ny <= n && nx > 0 && nx <= n) {
				if (map[ny][nx] == 0) {
					q.push({ ndir, {ny, nx} });
				}
			}

			// 세로로 이동
			ny = y + 1;
			nx = x;
			ndir = 2;

			if (ny > 0 && ny <= n && nx > 0 && nx <= n) {
				if (map[ny][nx] == 0) {
					q.push({ ndir, {ny, nx} });
				}
			}

			// 대각선 이동
			ny = y + 1;
			nx = x + 1;
			ndir = 3;

			if (ny > 0 && ny <= n && nx > 0 && nx <= n) {
				if (map[ny][nx] == 0 && map[ny][nx - 1] == 0 && map[ny - 1][nx] == 0) {
					q.push({ ndir,{ny,nx} });
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	bfs();

	cout << result;
}