#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
#include<memory.h>

using namespace std;

int n;
char map[101][101];
int abnormal = 0;
int normal = 0;
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };
bool check[101][101];

void bfs_ab(int Y, int X)
{
	if (check[Y][X] == false)
		abnormal++;

	queue<pair<int, int>>q;
	q.push({ Y,X });
	check[Y][X] = true;

	if (map[Y][X] == 'R' || map[Y][X] == 'G') {
		while (!q.empty())
		{
			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++)
			{
				int ny = y + dy[i];
				int nx = x + dx[i];

				if (ny >= 0 && ny < n && nx >= 0 && nx < n)
				{
					if (check[ny][nx] == false)
					{
						if (map[ny][nx] == 'G' || map[ny][nx] == 'R')
						{
							q.push({ ny,nx });
							check[ny][nx] = true;
						}
					}
				}
			}
		}
	}
	else if (map[Y][X] == 'B')
	{
		while (!q.empty())
		{
			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++)
			{
				int ny = y + dy[i];
				int nx = x + dx[i];

				if (ny >= 0 && ny < n && nx >= 0 && nx < n)
				{
					if (check[ny][nx] == false)
					{
						if (map[ny][nx] == 'B')
						{
							q.push({ ny,nx });
							check[ny][nx] = true;
						}
					}
				}
			}
		}
	}
}

void bfs_normal(int Y, int X)
{
	if (check[Y][X] == false)
		normal++;

	queue<pair<int, int>>q;
	q.push({ Y,X });
	check[Y][X] = true;
	char color = map[Y][X];

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny >= 0 && ny < n && nx >= 0 && nx < n)
			{
				if (check[ny][nx] == false)
				{
					if (color == map[ny][nx])
					{
						q.push({ ny,nx });
						check[ny][nx] = true;
					}
				}
			}
		}
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		for (int j = 0; j < s.size(); j++)
		{
			map[i][j] = s[j];
			check[i][j] = false;
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			bfs_ab(i, j);

	memset(check, false, sizeof(check));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			bfs_normal(i, j);

	cout << normal << ' ' << abnormal;
}