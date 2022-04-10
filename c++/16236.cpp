#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>

using namespace std;

int n;
int Map[21][21];
pair<pair<int, int>,int>shark;
int dy[4] = { 0,0,-1,1 };
int dx[4] = { 1,-1,0,0 };

int dist = 987654321;
int eat_x = 0;
int eat_y = 0;
int check[21][21];

void make_map()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 9) {
				shark.first = { i,j };
				shark.second = 2;
			}
			check[i][j] = -1;
		}
	}
}

void bfs(pair<pair<int,int>,int>S)
{
	int w = S.second;
	int Y = S.first.first;
	int X = S.first.second;
	check[Y][X] = 0;

	queue<pair<int, int>>q;
	q.push({ Y,X });

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny >= 1 && ny <= n && nx >= 1 && nx <= n)
			{
				if (check[ny][nx] != -1 || Map[ny][nx] > w) {
					continue;
				}

				check[ny][nx] = check[y][x] + 1;

				if (Map[ny][nx] > 0 && Map[ny][nx] < w) {
					if (dist > check[ny][nx]) {
						eat_y = ny;
						eat_x = nx;
						dist = check[ny][nx];
					}

					else {
						if (dist == check[ny][nx]) {
							if (eat_y == ny) {
								if (eat_x > nx) {
									eat_x = nx;
								}
							}
							else if (eat_y > ny) {
								eat_y = ny;
								eat_x = nx;
							}
						}
					}
				}
				q.push({ ny,nx });
			}
		}
	}
}

int solve()
{
	int time = 0;
	int cnt = 0;
	
	while (1)
	{
		memset(check, -1, sizeof(check));
		eat_x = 0;
		eat_y = 0;
		dist = 987654321;

		bfs(shark);

		if (eat_x == 0 && eat_y == 0)
			break;

		time += check[eat_y][eat_x];
		cnt++;
		Map[eat_y][eat_x] = 9;
		Map[shark.first.first][shark.first.second] = 0;
		shark.first = { eat_y,eat_x };

		if (cnt == shark.second) {
			cnt = 0;
			shark.second++;
		}
	}

	return time;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	make_map();
	int answer = solve();
	cout << answer;
}