#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>

using namespace std;

int T, L;
pair<int, int>start;
pair<int, int>finish;
int dx[8] = { 2,1,-1,-2,-2,-1,1,2 };
int dy[8] = { -1,-2,-2,-1,1,2,2,1 };
bool check[300][300];
int cache[300][300];

int bfs(int Y, int X, int endy, int endx, int cnt)
{
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++)
		{
			check[i][j] = false;
			cache[i][j] = 987654321;
		}
	}

	queue<pair<int, int>>q;
	q.push({ Y,X });
	check[Y][X] = true;
	cache[Y][X] = 0;

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;
		if (y == endy && x == endx)
			return cache[y][x];

		q.pop();
		for (int i = 0; i < 8; i++)
		{
			int ny, nx;
			ny = y + dy[i];
			nx = x + dx[i];
			if (ny >= 0 && ny < L && nx >= 0 && nx < L)
			{
				if (check[ny][nx] == false)
				{
					check[ny][nx] = true;
					q.push({ ny,nx });
					cache[ny][nx] = min(cache[ny][nx], cache[y][x] + 1);
				}
			}
		}
	}
}

int main()
{
	cin >> T;
	vector<int>res;
	while (T--)
	{
		cin >> L;
		int s1, s2, f1, f2;
		cin >> s1 >> s2;
		cin >> f1 >> f2;
		start = { s1,s2 };
		finish = { f1,f2 };
		res.push_back(bfs(s1, s2, f1, f2, 0));
	}
	for (int i = 0; i < res.size(); i++)
		cout << res[i] << '\n';
}