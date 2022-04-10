#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int m, n, k;
int map[101][101];
bool check[101][101];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };
int cnt = 0;
vector<int>res;

void make_map(int x1, int y1, int x2, int y2)
{
	for (int i = y1; i < y2; i++)
		for (int j = x1; j < x2; j++)
			map[i][j] = 1;
}

int bfs(int y, int x)
{
	cnt = 1;
	check[y][x] = true;
	queue<pair<int, int>>q;
	q.push({ y,x });

	while (!q.empty())
	{
		int ny = q.front().first;
		int nx = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int yy = ny + dy[i];
			int xx = nx + dx[i];

			if (yy >= 0 && yy < m && xx >= 0 && xx < n)
			{
				if (check[yy][xx] == false && map[yy][xx] == 0)
				{
					check[yy][xx] = true;
					q.push({ yy,xx });
					cnt += 1;
				}
			}
		}
	}
	return cnt;
}

int main()
{
	cin >> m >> n >> k;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			map[i][j] = 0;
			check[i][j] = false;
		}

	for (int i = 0; i < k; i++)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		make_map(x1, y1, x2, y2);
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] == 0 && check[i][j] == false)
			{
				int result = bfs(i, j);
				res.push_back(result);
			}
		}
	}
	sort(res.begin(), res.end());
	cout << res.size() << '\n';
	for (int i = 0; i < res.size(); i++)
		cout << res[i] << ' ';
}