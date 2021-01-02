#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

int r, c, t;
int room[50][50];
int spread_dust[50][50];
int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,1,-1 };
pair<int, int>air1 = { -1,-1 };
pair<int, int>air2 = { -1,-1 };

void make_room()
{
	cin >> r >> c >> t;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> room[i][j];
			if (room[i][j] == -1)
			{
				if (air1.first == -1) {
					air1.first = i;
					air1.second = j;
				}
				else {
					air2.first = i;
					air2.second = j;
				}
			}
		}
	}
}

void spread()
{
	memset(spread_dust, 0, sizeof(spread_dust));
	spread_dust[air1.first][air1.second] = -1;
	spread_dust[air2.first][air2.second] = -1;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			int dust = room[i][j];
			if (dust == 0 || dust == -1)
				continue;
			int ndust = dust / 5;
			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (ny >= 0 && ny < r && nx >= 0 && nx < c) {
					if (room[ny][nx] != -1) {
						spread_dust[ny][nx] += ndust;
						spread_dust[i][j] -= ndust;
					}
				}
			}
		}
	}

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (room[i][j] != -1) {
				room[i][j] += spread_dust[i][j];
			}
		}
	}
}

void activate_up()
{
	int tmp1 = room[air1.first][c - 1];
	int tmp2 = room[0][c - 1];
	int tmp3 = room[0][0];

	for (int x = c - 2; x > air1.second; x--) {
		room[air1.first][x + 1] = room[air1.first][x];
	}
	room[air1.first][air1.second + 1] = 0;
	for (int y = 1; y < air1.first; y++) {
		room[y - 1][c - 1] = room[y][c - 1];
	}
	room[air1.first - 1][c - 1] = tmp1;
	for (int x = 0; x < c - 2; x++) {
		room[0][x] = room[0][x + 1];
	}
	room[0][c - 2] = tmp2;
	for (int y = air1.first - 1; y > 1; y--) {
		room[y][0] = room[y - 1][0];
	}
	room[1][0] = tmp3;
}

void activate_down()
{
	int tmp1 = room[air2.first][c - 1];
	int tmp2 = room[r - 1][c - 1];
	int tmp3 = room[r - 1][0];
	
	for (int x = c - 2; x > air2.second; x--) {
		room[air2.first][x + 1] = room[air2.first][x];
	}
	room[air2.first][air2.second + 1] = 0;
	for (int y = r - 1; y > air2.first + 1; y--) {
		room[y][c - 1] = room[y - 1][c - 1];
	}
	room[air2.first + 1][c - 1] = tmp1;
	for (int x = 0; x < c - 2; x++) {
		room[r - 1][x] = room[r - 1][x + 1];
	}
	room[r - 1][c - 2] = tmp2;
	for (int y = air2.first + 1; y < r - 2; y++) {
		room[y][0] = room[y + 1][0];
	}
	room[r - 2][0] = tmp3;
}

int result()
{
	int res = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			res += room[i][j];

	res += 2; //공기청정기 -2 
	return res;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_room();
	while (t--) {
		spread();
		activate_up();
		activate_down();
	}
	cout << result();
}