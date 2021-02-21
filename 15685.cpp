#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

int n, x, y, d, g;
bool map[101][101]; 
vector<pair<int, int>>rot; // 시작점 -> 끝점까지 이동 방향 (dy,dx)

void rotation(int last_y, int last_x) // last_y, last_x : 끝점 
{
	vector<pair<int, int>>tmp;
	int size = rot.size();
	for (int i = size - 1; i >= 0; i--) {

		// dy, dx는 시작점으로부터의 방향
		int dy = rot[i].first;
		int dx = rot[i].second;

		// 역방향으로 변환
		dy = (-1) * dy;
		dx = (-1) * dx;

		// 역방향을 시계방향 90도로 회전시킨 것을 붙힌 것과 같음
		if (dy == 1 && dx == 0) {
			dy = 0;
			dx = -1;
			tmp.push_back({ dy,dx });
		}

		else if (dy == -1 && dx == 0) {
			dy = 0;
			dx = 1;
			tmp.push_back({ dy,dx });
		}

		else if (dy == 0 && dx == 1) {
			dy = 1;
			dx = 0;
			tmp.push_back({ dy,dx });
		}

		else {
			dy = -1;
			dx = 0;
			tmp.push_back({ dy,dx });
		}
	}

	// 회전한 거 붙히기
	int tmp_size = tmp.size();
	for (int i = 0; i < tmp_size; i++) {
		int dy = tmp[i].first;
		int dx = tmp[i].second;

		last_y += dy;
		last_x += dx;

		if (last_y >= 0 && last_y <= 100 && last_x >= 0 && last_x <= 100)
			map[last_y][last_x] = true;

		rot.push_back({ dy,dx });
	}

	tmp.clear();
	y = last_y;
	x = last_x;
}

int check()
{
	int res = 0;
	// 매 점마다 우, 우하, 하 추가로 3개 점 체크
	int dy[3] = { 0,1,1 };
	int dx[3] = { 1,1,0 };

	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			int cnt = 0;
			if (map[i][j]) {
				cnt++;
				for (int k = 0; k < 3; k++) {
					int ni = i + dy[k];
					int nj = j + dx[k];
					if (ni >= 0 && ni <= 100 && nj >= 0 && nj <= 100) {
						if (map[ni][nj])
							cnt++;
					}
				}
			}
			if (cnt == 4)
				res++;
		}
	}

	return res;
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		rot.clear();
		cin >> x >> y >> d >> g;

		map[y][x] = true;
		switch (d) {
		case 0:
			rot.push_back({ 0,1 });
			x += 1;
			break;
		case 1:
			rot.push_back({ -1,0 });
			y += -1;
			break;
		case 2:
			rot.push_back({ 0,-1 });
			x += -1;
			break;
		case 3:
			rot.push_back({ 1,0 });
			y += 1;
			break;
		default:
			break;
		}

		if (g == 0) {
			map[y][x] = true;
		}

		else {
			map[y][x] = true;
			while (g--) {
				rotation(y, x);
			}
		}
	}
	cout << check();
}