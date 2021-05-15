#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

int k, w, h;
int map[201][201];
int cnt[201][201][31];
int dy[4] = { 0,0,1,-1 }; // 1칸씩 움직이는 경우
int dx[4] = { 1,-1,0,0 };
int dhy[8] = { -1,-2,-2,-1,1,2,2,1 }; // 말처럼 움직이는 경우
int dhx[8] = { 2,1,-1,-2,-2,-1,1,2 };
int inf = 987654321;

void init()
{
	cin >> k;
	cin >> w >> h;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> map[i][j];
			for (int t = 0; t <= k; t++)
				cnt[i][j][t] = inf;
		}
	}
}

int bfs()
{
	// {k 횟수, {위치}}
	queue<pair<int, pair<int, int>>>q;
	q.push({ 0,{0,0} });
	cnt[0][0][0] = 0;

	int min_r = 0;
	while (!q.empty())
	{
		int r = q.front().first;
		int y = q.front().second.first;
		int x = q.front().second.second;

		q.pop();

		// 도착 완료
		if (y == h - 1 && x == w - 1) {
			min_r = r;
			break;
		}

		// 불가능한 경우
		if (r > k)
			continue;

		// 말처럼 움직이는 횟수 다 씀
		else if (r == k) {
			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				
				if (ny < 0 || ny >= h || nx < 0 || nx >= w)
					continue;

				if (map[ny][nx] == 1)
					continue;

				if (cnt[ny][nx][r] > cnt[y][x][r] + 1) {
					cnt[ny][nx][r] = cnt[y][x][r] + 1;
					q.push({ r,{ny,nx} });
				}
			}
		}

		// 말처럼 움직이는 횟수 남음
		else {
			// 그냥 1칸 움직임
			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];

				if (ny < 0 || ny >= h || nx < 0 || nx >= w)
					continue;

				if (map[ny][nx] == 1)
					continue;

				if (cnt[ny][nx][r] > cnt[y][x][r] + 1) {
					cnt[ny][nx][r] = cnt[y][x][r] + 1;
					q.push({ r,{ny,nx} });
				}
			}
			// 말처럼 움직임
			for (int i = 0; i < 8; i++) {
				int ny = y + dhy[i];
				int nx = x + dhx[i];

				if (ny < 0 || ny >= h || nx < 0 || nx >= w)
					continue;

				if (map[ny][nx] == 1)
					continue;

				if (cnt[ny][nx][r + 1] > cnt[y][x][r] + 1) {
					cnt[ny][nx][r + 1] = cnt[y][x][r] + 1;
					q.push({ r + 1,{ny,nx} });
				}
			}
		}
	}

	return cnt[h - 1][w - 1][min_r];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	
	int res = bfs();
	if (res == inf)
		cout << -1;
	else
		cout << res;
}