#include<iostream>
#include<vector>
#include<algorithm>
#include<memory.h>

using namespace std;

int map[20][20];
int dx[4] = { 0,1,1,1 };
int dy[4] = { 1,0,1,-1 };
int winner = 0;

void make_map()
{
	for (int i = 1; i < 20; i++)
		for (int j = 1; j < 20; j++)
			cin >> map[i][j];
}

pair<int, int> result(pair<int, int>left)
{
	for (int i = 1; i < 20; i++)
	{
		for (int j = 1; j < 20; j++)
		{
			if (map[i][j] == 1)
			{
				left = { i,j };

				for (int k = 0; k < 4; k++)
				{
					int nx = dx[k];
					int ny = dy[k];
					int x = left.second;
					int y = left.first;

					if (y >= 1 && x >= 1 && y <= 19 && x <= 19 && y + 4 * ny >= 1 && x + 4 * nx >= 1 && y + 4 * ny <= 19 && x + 4 * nx <= 19)
					{
						if (map[y + ny][x + nx] == 1 && map[y + 2 * ny][x + 2 * nx] == 1 && map[y + 3 * ny][x + 3 * nx] == 1 && map[y + 4 * ny][x + 4 * nx] == 1)
						{
							if (y + 5 * ny >= 1 && x + 5 * nx >= 1 && y + 5 * ny <= 19 && x + 5 * nx <= 19 && map[y + 5 * ny][x + 5 * nx] == 1)
								continue;
							if (y - ny >= 1 && x - nx >= 1 && y - ny <= 19 && x - nx <= 19 && map[y - ny][x - nx] == 1)
								continue;
							winner = 1;
							return left;
						}
					}
				}
			}
			if (map[i][j] == 2)
			{
				left = { i,j };

				for (int k = 0; k < 4; k++)
				{
					int nx = dx[k];
					int ny = dy[k];
					int x = left.second;
					int y = left.first;

					if (y >= 1 && x >= 1 && y <= 19 && x <= 19 && y + 4 * ny >= 1 && x + 4 * nx >= 1 && y + 4 * ny <= 19 && x + 4 * nx <= 19)
					{
						if (map[y + ny][x + nx] == 2 && map[y + 2 * ny][x + 2 * nx] == 2 && map[y + 3 * ny][x + 3 * nx] == 2 && map[y + 4 * ny][x + 4 * nx] == 2)
						{
							if (y + 5 * ny >= 1 && x + 5 * nx >= 1 && y + 5 * ny <= 19 && x + 5 * nx <= 19 && map[y + 5 * ny][x + 5 * nx] == 2)
								continue;
							if (y - ny >= 1 && x - nx >= 1 && y - ny <= 19 && x - nx <= 19 && map[y - ny][x - nx] == 2)
								continue;
							winner = 2;
							return left;
						}
					}
				}
			}
		}
	}
	return { 0,0 };
}

int main()
{
	make_map();
	pair<int, int>left = { 0,0 };
	left = result(left);

	if (winner == 0)
		cout << 0;
	else
	{
		if (winner == 1)
		{
			cout << 1 << '\n';
			cout << left.first << ' ' << left.second;
		}
		else
		{
			cout << 2 << '\n';
			cout << left.first << ' ' << left.second;
		}
	}
}