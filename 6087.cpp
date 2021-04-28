#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
#include<string>
#include<cstdio>

using namespace std;

int w, h;
char map[101][101];
pair<int, int>p1 = { -1,-1 }; // c의 한 점
pair<int, int>p2 = { -1,-1 }; // c의 다른 점
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 }; // 상하좌우 index = 0,1,2,3
int check[101][101]; 
// check : 거울 설치 개수
// 해당 점의 check값보다 작은 경우로 들어오면 
// 해당 점까지 더 적게 거울 설치하는 경우 존재

void make_map()
{
	cin >> w >> h;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'C') {
				if (p1.first == -1) {
					p1 = { i,j };
				}
				else {
					p2 = { i,j };
				}
			}
			check[i][j] = 987654321;
		}
	}
}

// 가능한 빛의 경로인지 파악
// -1이면 안 되는 경우
// 0이면 직진하는 경우
// 1이면 90도로 꺾이는 경우
int possible(int dir, int ndir)
{
	if (dir == 0 && ndir == 1)
		return -1;
	else if (dir == 1 && ndir == 0)
		return -1;
	else if (dir == 2 && ndir == 3)
		return -1;
	else if (dir == 3 && ndir == 2)
		return -1;
	else if (dir == ndir)
		return 0;
	else
		return 1;
}

// 다음 위치로의 방향 구하기
int cal_dir(int y, int x, int ny, int nx)
{
	// 상하좌우 0123
	if (y > ny && x == nx)
		return 0;
	else if (y < ny && x == nx)
		return 1;
	else if (y == ny && x > nx)
		return 2;
	else if (y == ny && x < nx)
		return 3;
	else
		return -1;
}

int bfs()
{
	// 우선순위 큐 오름차순 정렬
	// 체크 값 -1이면 갱신하고 큐 삽입
	// 아니면 체크 값이 작아지는 경우만 큐 삽입
	// 큐 : { {거울 설치 횟수, 빛 방향}, { 위치 y, x} }
	// 빛 방향 : 0123 순 상하좌우
	priority_queue<pair<pair<int,int>, pair<int, int>>, vector<pair<pair<int,int>,pair<int,int>>>, greater<pair<pair<int,int>, pair<int,int>>> >q;
	//queue < pair<pair<int, int>, pair<int, int>>>q;
	q.push({ {0,0},{p1.first, p1.second} });
	q.push({ {0,1},{p1.first, p1.second} });
	q.push({ {0,2},{p1.first, p1.second} });
	q.push({ {0,3},{p1.first, p1.second} });
	check[p1.first][p1.second] = 0;

	int result = 0;

	while (!q.empty())
	{
		int y = q.top().second.first;
		int x = q.top().second.second;
		int cnt = q.top().first.first;
		int dir = q.top().first.second;
		//int y = q.front().second.first;
		//int x = q.front().second.second;
		//int cnt = q.front().first.first;
		//int dir = q.front().first.second;

		if (y == p2.first && x == p2.second) {
			q.pop();
			continue;
		}

		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			int ndir = cal_dir(y, x, ny, nx);
			int ncnt = cnt;

			if (ny >= 0 && ny < h && nx >= 0 && nx < w) {
				// 벽이면 진행 불가
				if (map[ny][nx] == '*')
					continue;
				// 상하좌우 아닌 경우
				if (ndir == -1)
					continue;
				
				int pos = possible(dir, ndir);
				// 반대방향으로 빛 못움직임
				if (pos == -1)
					continue;
				else {
					// 꺾이는 경우
					if (pos == 1)
						ncnt++;
					if (check[ny][nx] >= ncnt) {
						check[ny][nx] = ncnt;
						q.push({ {ncnt, ndir},{ny,nx} });
					}
				}
			}
		}
	}

	result = check[p2.first][p2.second];
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//freopen("input.txt", "r", stdin);

	make_map();
	int result = bfs();

	cout << result;
}