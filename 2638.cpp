#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int n, m;
int map[101][101]; //  치즈 맵
bool air[101][101]; // 바깥 공기, true면 바깥 공기
bool check[101][101]; // 탐색불가, 이미 탐색 : false, 탐색 가능 : true
vector<pair<int, int>>v; // 없어질 치즈 위치 {y,x}
int time;
int cheese; // 전체 치즈 개수, 0되면 time 그만 계산

int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };

void make_map()
{
	cin >> n >> m;

	time = 0;
	cheese = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0)
				check[i][j] = false;
			else {
				check[i][j] = true;
				cheese++;
			}
			air[i][j] = false;
		}
	}
}

// 처음 바깥 공기 구하기
void first_Air()
{
	queue<pair<int, int>>q;
	q.push({ 0,0 }); // 맨 가장자리는 공기
	air[0][0] = true;

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny >= 0 && ny < n && nx >= 0 && nx < m) {
				if (air[ny][nx])
					continue;

				if (map[ny][nx] == 0) {
					q.push({ ny,nx });
					air[ny][nx] = true;
				}
			}
		}
	}
}

// 없어지는 치즈인지 체크 여부 true면 없어질 치즈
bool bye(int y, int x)
{
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny >= 0 && ny < n && nx >= 0 && nx < m) {
			if (air[ny][nx])
				cnt++;
		}
	}

	if (cnt >= 2)
		return true;
	else
		return false;
}

// {Y,X}부터 없어질 치즈 찾기
void bfs(int Y, int X)
{
	// {Y,X} : 탐색 시작 치즈 위치 (없어질 치즈)
	queue<pair<int, int>>q;
	q.push({ Y,X });
	check[Y][X] = false;
	
	if (bye(Y, X))
		v.push_back({ Y,X });

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			// 맵 안에 존재
			if (ny >= 0 && ny < n && nx >= 0 && nx < m)
			{
				// 탐색 가능한 경우
				if (check[ny][nx] == true) {
					// 없어질 치즈인 경우
					if (bye(ny, nx)) {
						v.push_back({ ny,nx });
					}
					q.push({ ny,nx });
					check[ny][nx] = false;
				}
			}
		}
	}
}

// 치즈 제거
void delete_cheese()
{
	for (int i = 0; i < v.size(); i++) {
		map[v[i].first][v[i].second] = 0;
	}
	cheese -= (int)(v.size());
}

// 새로운 바깥 공기, 제거된 치즈는 바깥 공기이므로 
// 얘네들로 bfs 돌려서 새로운 바깥 공기 구할 수 있다.
void new_Air()
{
	queue<pair<int, int>>q;
	for (int i = 0; i < v.size(); i++) {
		q.push({ v[i].first, v[i].second });
		air[v[i].first][v[i].second] = true;
	}

	v.clear();

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			
			if (ny >= 0 && ny < n && nx >= 0 && nx < m) {
				if (map[ny][nx] == 0) {
					if (air[ny][nx] == false) {
						q.push({ ny,nx });
						air[ny][nx] = true;
					}
				}
			}
		}
	}
}

void init_check()
{
	memset(check, false, sizeof(check));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 1)
				check[i][j] = true;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_map();

	first_Air();

	while (cheese != 0)
	{
		init_check();

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == 1) {
					if (check[i][j]) {
						bfs(i, j);
					}
				}
			}
		}

		delete_cheese();
		new_Air();
		time++;
	}

	cout << time;
}