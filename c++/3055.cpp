#include<iostream>
#include<queue>
#include<string>

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

int r, c;
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,1,-1 };
char forest[50][50];
string fail = "KAKTUS";

pair<int, int>cave; // 동굴 위치
pair<int, int>hedge; // 고슴도치 = hedgedog

int water_day[50][50] = { {0,}, }; // 물이 해당 칸에 차는데 걸리는 시간
int move_day[50][50] = { {0,}, }; // 고슴도치가 해당 칸까지 이동하는데 걸리는 시간 
// 고슴도치가 이동한 칸이 물이 차는 날보다 작으면 이동 가능

queue<pair<int, int>>water; // 물의 위치

void make_forest()
{
	cin >> r >> c;
	for (int i = 0; i < r; i++)
	{
		string s;
		cin >> s;
		for (int j = 0; j < c; j++) {
			forest[i][j] = s[j];
			if (forest[i][j] == 'D')
				cave = { i,j };
			if (forest[i][j] == 'S')
				hedge = { i,j };
			if (forest[i][j] == '*')
				water.push({ i,j });
		}
		s.clear();
	}
}

void water_bfs()
{
	while (!water.empty()) {
		int wy = water.front().first;
		int wx = water.front().second;
		water.pop();

		for (int i = 0; i < 4; i++) {
			int nwy = wy + dy[i];
			int nwx = wx + dx[i];

			if (nwy >= 0 && nwy < r && nwx >= 0 && nwx < c && water_day[nwy][nwx] == 0) {
				if (forest[nwy][nwx] == '.') {
					water_day[nwy][nwx] = water_day[wy][wx] + 1;
					water.push({ nwy,nwx });
				}
			}
		}
	}
}

void move_bfs()
{
	int Y = hedge.first;
	int X = hedge.second;

	queue<pair<int, int>>move_hedge;
	move_hedge.push({ Y,X });

	while (!move_hedge.empty()) {
		int y = move_hedge.front().first;
		int x = move_hedge.front().second;
		move_hedge.pop();

		if (y == cave.first && x == cave.second) {
			break;
		}

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny >= 0 && ny < r && nx >= 0 && nx < c) {
				if (move_day[ny][nx] == 0 && (forest[ny][nx] == '.' || forest[ny][nx] == 'D')) {
					if (water_day[ny][nx] == 0) {
						move_hedge.push({ ny,nx });
						move_day[ny][nx] = move_day[y][x] + 1;
					}
					else {
						if (water_day[ny][nx] > move_day[y][x] + 1) {
							move_hedge.push({ ny,nx });
							move_day[ny][nx] = move_day[y][x] + 1;
						}
					}
				}
			}
		}
	}
}

int main()
{
	make_forest();
	water_bfs();
	move_bfs();

	if (move_day[cave.first][cave.second] == 0)
		cout << fail;
	else
		cout << move_day[cave.first][cave.second];
}