#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<string>
#include<queue>

using namespace std;

int r, c;
char map[51][51];
int dist[51][51];
bool check[51][51];
int result;

int dy[4] = { 0,0,-1,1 };
int dx[4] = { 1,-1,0,0 };

void make_map()
{
	cin >> r >> c;
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++) {
			cin >> map[i][j];
		}
	}
}

void init()
{
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			dist[i][j] = 0;
			check[i][j] = false;
		}
	}
}

int bfs(int Y, int X)
{
	queue<pair<int, int>>q;
	q.push({ Y,X });
	int res = 0;
	dist[Y][X] = 0;
	check[Y][X] = true;

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;
		int d = dist[y][x];

		q.pop();
		res = max(res, d);

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny >= 0 && ny < r && nx >= 0 && nx < c) {
				if (check[ny][nx]==false && map[ny][nx] == 'L') {
					q.push({ ny,nx });
					dist[ny][nx] = dist[y][x] + 1;
					check[ny][nx] = true;
				}
			}
		}
	}

	return res;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_map();

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] == 'L') {
				init();
				result = max(result, bfs(i, j));
			}
		}
	}

	cout << result;
}