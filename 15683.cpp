#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<string>
#include<cstring>
#include<cstdlib>

using namespace std;

int n, m;
int Map[9][9];
vector<pair<int, int>>cctv;
int result = 0;
int cnt = 0;
int wall = 0;

// 1: 한 방향 2: 양방향 
// 3: 직각방향 4: 세 방향 
// 5: 네 방향 6: 벽

void make_map()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> Map[i][j];
			if (Map[i][j] != 0 && Map[i][j] != 6)
				cctv.push_back({ i,j });
			if (Map[i][j] == 6)
				wall++;
		}
	}
}

void y_plus(int y, int x)
{
	for (int i = y; i <= n; i++)
	{
		if (Map[i][x] == 6)
			break;
		else {
			if (Map[i][x] == 0) {
				Map[i][x] = -1;
				cnt++;
			}
			else
				continue;
		}
	}
}

void y_minus(int y, int x)
{
	for (int i = y; i >= 1; i--)
	{
		if (Map[i][x] == 6)
			break;
		else {
			if (Map[i][x] == 0) {
				Map[i][x] = -1;
				cnt++;
			}
			else
				continue;
		}
	}
}

void x_plus(int y, int x)
{
	for (int i = x; i <= m; i++)
	{
		if (Map[y][i] == 6)
			break;
		else {
			if (Map[y][i] == 0) {
				Map[y][i] = -1;
				cnt++;
			}
			else
				continue;
		}
	}
}

void x_minus(int y, int x)
{
	for (int i = x; i >= 1; i--)
	{
		if (Map[y][i] == 6)
			break;
		else {
			if (Map[y][i] == 0) {
				Map[y][i] = -1;
				cnt++;
			}
			else
				continue;
		}
	}
}

int one(int y, int x, int idx)
{
	if (idx == 0)
	{
		cnt = 0;
		y_plus(y, x);
		return cnt;
	}
	else if (idx == 1)
	{
		cnt = 0;
		x_minus(y, x);
		return cnt;
	}
	else if (idx == 2)
	{
		cnt = 0;
		y_minus(y, x);
		return cnt;
	}
	else if (idx == 3)
	{
		cnt = 0;
		x_plus(y, x);
		return cnt;
	}
}

int two(int y, int x, int idx)
{
	if (idx == 0 || idx == 2)
	{

		cnt = 0;
		y_plus(y, x);
		y_minus(y, x);
		return cnt;
	}
	else if (idx == 1 || idx == 3)
	{
		cnt = 0;
		x_plus(y, x);
		x_minus(y, x);
		return cnt;
	}
}

int three(int y, int x, int idx)
{
	if (idx == 0)
	{
		cnt = 0;
		y_plus(y, x);
		x_plus(y, x);
		return cnt;
	}
	else if (idx == 1)
	{
		cnt = 0;
		y_plus(y, x);
		x_minus(y, x);
		return cnt;
	}
	else if (idx == 2)
	{
		cnt = 0;
		y_minus(y, x);
		x_minus(y, x);
		return cnt;
	}
	else if (idx == 3)
	{
		cnt = 0;
		y_minus(y, x);
		x_plus(y, x);
		return cnt;
	}
}

int four(int y, int x, int idx)
{
	if (idx == 0)
	{
		cnt = 0;
		y_plus(y, x);
		y_minus(y, x);
		x_minus(y, x);
		return cnt;
	}
	else if (idx == 1)
	{
		cnt = 0;
		y_plus(y, x);
		x_minus(y, x);
		x_plus(y, x);
		return cnt;
	}
	else if (idx == 2)
	{
		cnt = 0;
		y_plus(y, x);
		y_minus(y, x);
		x_plus(y, x);
		return cnt;
	}
	else if (idx == 3)
	{
		cnt = 0;
		y_minus(y, x);
		x_plus(y, x);
		x_minus(y, x);
		return cnt;
	}
}

int five(int y, int x, int idx)
{
	cnt = 0;
	y_plus(y, x);
	y_minus(y, x);
	x_plus(y, x);
	x_minus(y, x);
	return cnt;
}

void dfs(int n, int res)
{
	if (res > result)
		result = res;

	if (n == cctv.size())
		return;

	int y = cctv[n].first;
	int x = cctv[n].second;

	int Map_copy[9][9];
	memcpy(Map_copy, Map, sizeof(Map));

	if (Map[y][x] == 1)
	{
		for (int idx = 0; idx < 4; idx++)
		{
			memcpy(Map, Map_copy, sizeof(Map_copy));
			int tmp = res;
			res += one(y, x, idx);
			dfs(n + 1, res);
			res = tmp;
		}
	}
	if (Map[y][x] == 2)
	{
		for (int idx = 0; idx < 4; idx++)
		{
			memcpy(Map, Map_copy, sizeof(Map_copy));
			int tmp = res;
			res += two(y, x, idx);
			dfs(n + 1, res);
			res = tmp;
		}
	}
	if (Map[y][x] == 3)
	{
		for (int idx = 0; idx < 4; idx++)
		{
			memcpy(Map, Map_copy, sizeof(Map_copy));
			int tmp = res;
			res += three(y, x, idx);
			dfs(n + 1, res);
			res = tmp;
		}
	}
	if (Map[y][x] == 4)
	{
		for (int idx = 0; idx < 4; idx++)
		{
			memcpy(Map, Map_copy, sizeof(Map_copy));
			int tmp = res;
			res += four(y, x, idx);
			dfs(n + 1, res);
			res = tmp;
		}
	}
	if (Map[y][x] == 5)
	{
		for (int idx = 0; idx < 4; idx++)
		{
			memcpy(Map, Map_copy, sizeof(Map_copy));
			int tmp = res;
			res += five(y, x, idx);
			dfs(n + 1, res);
			res = tmp;
		}
	}
}

int main()
{
	make_map();
	dfs(0, 0);
	cout << (n * m) - result - cctv.size() - wall;
}
