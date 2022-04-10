#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>

using namespace std;

int n, k;
int L;
vector<pair<int, char>>change;
deque<pair<int, int>>snake;
int map[101][101];

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
//µ¿¼­³²ºÏ 0123
int dir = 0;
int time = 0;
pair<int, int>head = { 1,1 };
int idx = 0;

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			map[i][j] = 0;

	cin >> k;
	for (int i = 0; i < k; i++)
	{
		int a, b;
		cin >> a >> b;
		map[a][b] = 1;
	}

	cin >> L;
	for (int i = 0; i < L; i++)
	{
		int a;
		char b;
		cin >> a >> b;
		change.push_back({ a,b });
	}

	map[1][1] = 2;
	snake.push_back({ 1,1 });
	int x = head.second;
	int y = head.first;

	while (1)
	{
		time += 1;

		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (ny<1 || ny>n || nx<1 || nx>n || map[ny][nx] == 2)
			break;

		else if (map[ny][nx] == 0)
		{
			map[ny][nx] = 2;
			map[snake.back().first][snake.back().second] = 0;
			snake.pop_back();
			snake.push_front({ ny,nx });
		}
		else if (map[ny][nx] == 1)
		{
			map[ny][nx] = 2;
			snake.push_front({ ny,nx });
		}

		if (idx < change.size())
		{
			if (time == change[idx].first)
			{
				if (change[idx].second == 'D')
				{
					if (dir == 0)
						dir = 2;
					else if (dir == 1)
						dir = 3;
					else if (dir == 2)
						dir = 1;
					else
						dir = 0;
				}
				else
				{
					if (dir == 0)
						dir = 3;
					else if (dir == 1)
						dir = 2;
					else if (dir == 2)
						dir = 0;
					else
						dir = 1;
				}
				idx += 1;
			}
		}
		y = ny;
		x = nx;
	}
	cout << time;
}