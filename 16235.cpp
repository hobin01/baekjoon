#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>

using namespace std;

int n, m, k;
pair<vector<int>, int>map[11][11]; // first-나무 나이 순으로 second- 총 양분
vector<int>die[11][11];
int food[11][11]; //매년 추가되는 양분 양 // 처음 5
int res;
int dx[8] = { 1,1,0,-1,-1,-1,0,1 };
int dy[8] = { 0,-1,-1,-1,0,1,1,1 };

void spring()
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			vector<int>tmp;

			if (map[i][j].first.size() != 0)
			{
				sort(map[i][j].first.begin(), map[i][j].first.end());
				for (int t = 0; t < map[i][j].first.size(); t++)
				{
					if (map[i][j].first[t] > map[i][j].second) {
						die[i][j].push_back(map[i][j].first[t]);
						map[i][j].first[t] = 0;
					}
					else if (map[i][j].first[t] <= map[i][j].second && map[i][j].first[t] > 0)
					{
						map[i][j].second -= map[i][j].first[t];
						tmp.push_back(map[i][j].first[t] + 1);
					}
				}
			}
			map[i][j].first.clear();
			map[i][j].first = tmp;
			tmp.clear();
			//map[i][j].first.erase(remove(map[i][j].first.begin(), map[i][j].first.end(), 0), map[i][j].first.end());
		}
	}
}

void summer()
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (die[i][j].size() != 0)
			{
				for (int t = 0; t < die[i][j].size(); t++) {
					map[i][j].second += (die[i][j][t] / 2);
				}
			}
			die[i][j].clear();
			//map[i][j].first.erase(remove(map[i][j].first.begin(), map[i][j].first.end(), 0), map[i][j].first.end());
		}
	}
}

void fall()
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j].first.size() != 0) {
				for (int t = 0; t < map[i][j].first.size(); t++) {
					if (map[i][j].first[t] > 0 && map[i][j].first[t] % 5 == 0) {
						for (int s = 0; s < 8; s++) {
							int y = i + dy[s];
							int x = j + dx[s];
							if (y >= 1 && y <= n && x >= 1 && x <= n) {
								map[y][x].first.push_back(1);
							}
						}
					}
				}
			}
			//map[i][j].first.erase(remove(map[i][j].first.begin(), map[i][j].first.end(), 0), map[i][j].first.end());
		}
	}
}

void winter()
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j].second += food[i][j];
		}
	}
}

void delete_zero()
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j].first.size() != 0)
				map[i][j].first.erase(remove(map[i][j].first.begin(), map[i][j].first.end(), 0), map[i][j].first.end());
		}
	}
}


int main()
{
	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> food[i][j];
			map[i][j].second = 5;
		}
	}

	for (int i = 1; i <= m; i++) {
		int r, c, age;
		cin >> r >> c >> age;
		map[r][c].first.push_back(age);
	}

	while (k--) {
		spring();
		summer();
		fall();
		winter();
		//delete_zero();
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j].first.size() != 0)
				res += map[i][j].first.size();
		}
	}

	cout << res;
}