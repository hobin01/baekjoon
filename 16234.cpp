#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;

int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,1,-1 };
int n, L, R;
int map[51][51];
bool check[51][51];

void init_check()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			check[i][j] = false;
}

vector<pair<int, int>> bfs(int Y, int X)
{
	vector<pair<int, int>>country;
	queue<pair<int, int>>q;
	q.push({ Y,X });
	check[Y][X] = true;
	country.push_back({ Y,X });

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny >= 1 && ny <= n && nx >= 1 && nx <= n)
			{
				if (check[ny][nx] == false)
				{
					if (abs(map[y][x] - map[ny][nx]) >= L && abs(map[y][x] - map[ny][nx]) <= R)
					{
						check[ny][nx] = true;
						q.push({ ny,nx });
						country.push_back({ ny,nx });
					}
				}
			}
		}
	}
	return country;
}

void transfer(vector<pair<int, int>>v)
{
	int united = v.size();
	int total = 0;
	int ave = 0;
	if (united > 1)
	{
		for (int i = 0; i < united; i++)
		{
			pair<int, int>p = v[i];
			total += map[p.first][p.second];
		}
		ave = total / united;
		for (int i = 0; i < united; i++)
		{
			pair<int, int>p = v[i];
			map[p.first][p.second] = ave;
		}
	}
}

int main()
{
	cin >> n >> L >> R;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			cin >> map[i][j];
			check[i][j] = false;
		}

	int res = 0;
	while (1)
	{
		init_check();
		vector<vector<pair<int, int>>>V;
		int tmp = map[1][1];

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (check[i][j] == false)
					V.push_back(bfs(i, j));
			}
		}
		for (int i = 0; i < V.size(); i++)
		{
			transfer(V[i]);
		}

		if (V.size() == n * n && tmp == map[1][1])
			break;

		res += 1;
		V.clear();
	}

	cout << res;
}