#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int n, m;
int r, c, d;
int cnt = 0;
int map[50][50];

int next_x[4] = { 0,1,0,-1 };
int next_y[4] = { -1,0,1,0 };

int back_x[4] = { 0,-1,0,1 };
int back_y[4] = { 1,0,-1,0 };

void dfs(int x, int y, int d)
{
	if (map[y][x] == 0)
	{
		cnt += 1;
		map[y][x] = -1;
	}

	int dir;
	for (int dir = d - 1; dir > d - 5; dir--)
	{
		int ndir = (dir + 4) % 4;
		int nx = x + next_x[ndir];
		int ny = y + next_y[ndir];

		if (nx<0 || nx>(m - 1) || ny<0 || ny>(n - 1))
			continue;
		if (map[ny][nx] == 0)
		{
			dfs(nx, ny, ndir);
			return;
		}
	}

	if (map[y + back_y[d]][x + back_x[d]] == 1)
		return;
	else
		dfs(x + back_x[d], y + back_y[d], d);
}

int main()
{
	cin >> n >> m;
	cin >> r >> c >> d;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> map[i][j];


	dfs(c, r, d);
	cout << cnt;
}

