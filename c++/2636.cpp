#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

int r, c;
int map[101][101];
bool check[101][101]; // 치즈 한 덩이씩 구분
bool air[101][101]; // 바깥 공기 구분
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
int time = 0;
int cnt = 0;

void make_map()
{
	cin >> r >> c;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			cin >> map[i][j];

	memset(check, false, sizeof(check));
	memset(air, false, sizeof(air));
}

void bfs_cheese(int Y, int X)
{
	queue<pair<int, int>>q;
	q.push({ Y,X });
	check[Y][X] = true;

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny >= 0 && ny < r && nx >= 0 && nx < c) {
				if (map[ny][nx] == 1 && check[ny][nx] == false) {
					q.push({ ny,nx });
					check[ny][nx] = true;
				}
			}
		}
	}
}

void bfs_air(int Y, int X)
{
	queue<pair<int, int>>q;
	q.push({ Y,X });
	air[Y][X] = true;

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny >= 0 && ny < r && nx >= 0 && nx < c) {
				if (map[ny][nx] == 0 && air[ny][nx] == false) {
					q.push({ ny,nx });
					air[ny][nx] = true;
				}
			}
		}
	}
}


void delete_cheese()
{
	for (int i = 0; i < r; i++) {

		for (int j = 0; j < c; j++) {

			if (map[i][j] == 1 && check[i][j] == false) {
				bfs_cheese(i, j);
			}

			if (map[i][j] == 1 && check[i][j] == true) {

				for (int k = 0; k < 4; k++) {
					int nextY = i + dy[k];
					int nextX = j + dx[k];

					if (nextY >= 0 && nextY < r && nextX >= 0 && nextX < c) {
						if (map[nextY][nextX] == 0 && air[nextY][nextX] == true) {
							map[i][j] = 0;
						}
					}
				}

			}
		}
	}
}

int cheese_count()
{
	int res = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
		{
			if (map[i][j] == 1)
				res++;
		}
	}
	return res;
}


int main()
{
	make_map();

	while (cheese_count() != 0) {

		cnt = cheese_count();

		memset(check, false, sizeof(check));
		memset(air, false, sizeof(air));

		bfs_air(0, 0);
		delete_cheese();

		time++;

	}

	cout << time << '\n' << cnt;

}