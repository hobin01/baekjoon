#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int map[500][500];
int result;
vector<pair<int, int>>sand;
vector<pair<int, int>>tmp;

int percent[9] = { 1,1,7,7,2,2,10,10,5 };
int basic_sand;

void init()
{
	cin >> n;
	int num;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> num;
			map[i][j] = num;
		}
	}
	result = 0;
	basic_sand = 0;
	return;
}

bool is_in_map(int r, int c) {
	if (r < 0 || r >= n || c < 0 || c >= n)
		return false;
	else
		return true;
}

void make_sand(int r2, int c2, int dir)
{
	// 모래가 옮겨 갈 수 있는 위치 리턴
	// r2,c2 : y 위치
	sand.clear();
	tmp.clear();
	basic_sand = map[r2][c2];

	int y0, x0, y1, x1; // 1% 위치
	int y2, x2, y3, x3; // 7% 위치
	int y4, x4, y5, x5; // 2% 위치
	int y6, x6, y7, x7; // 10% 위치
	int y8, x8; // 5% 위치
	int y9, x9; // 알파 위치

	if (dir == 0) {
		y0 = r2 - 1; x0 = c2 + 1; y1 = r2 + 1; x1 = c2 + 1;
		y2 = r2 - 1; x2 = c2; y3 = r2 + 1; x3 = c2;
		y4 = r2 - 2; x4 = c2; y5 = r2 + 2; x5 = c2;
		y6 = r2 - 1; x6 = c2 - 1; y7 = r2 + 1; x7 = c2 - 1;
		y8 = r2; x8 = c2 - 2;
		y9 = r2; x9 = c2 - 1;

		tmp.push_back({ y0, x0 });
		tmp.push_back({ y1, x1 });
		tmp.push_back({ y2, x2 });
		tmp.push_back({ y3, x3 });
		tmp.push_back({ y4, x4 });
		tmp.push_back({ y5, x5 });
		tmp.push_back({ y6, x6 });
		tmp.push_back({ y7, x7 });
		tmp.push_back({ y8, x8 });
		tmp.push_back({ y9, x9 });

		for (int i = 0; i < 9; i++) {
			int ny = tmp[i].first;
			int nx = tmp[i].second;

			int new_sand = (map[r2][c2] * percent[i]) / 100;

			if (is_in_map(ny, nx) == false) {
				result += new_sand;
				basic_sand -= new_sand;
			}
			else {
				map[ny][nx] += new_sand;
				basic_sand -= new_sand;
			}
		}

		int alpha_y = tmp[9].first;
		int alpha_x = tmp[9].second;

		if (is_in_map(alpha_y, alpha_x) == false) {
			result += basic_sand;
		}
		else {
			map[alpha_y][alpha_x] += basic_sand;
		}

		map[r2][c2] = 0;
	}
	else if (dir == 1) {
		y0 = r2 - 1; x0 = c2 - 1; y1 = r2 + 1; x1 = c2 - 1;
		y2 = r2 - 1; x2 = c2; y3 = r2 + 1; x3 = c2;
		y4 = r2 - 2; x4 = c2; y5 = r2 + 2; x5 = c2;
		y6 = r2 - 1; x6 = c2 + 1; y7 = r2 + 1; x7 = c2 + 1;
		y8 = r2; x8 = c2 + 2;
		y9 = r2; x9 = c2 + 1;

		tmp.push_back({ y0, x0 });
		tmp.push_back({ y1, x1 });
		tmp.push_back({ y2, x2 });
		tmp.push_back({ y3, x3 });
		tmp.push_back({ y4, x4 });
		tmp.push_back({ y5, x5 });
		tmp.push_back({ y6, x6 });
		tmp.push_back({ y7, x7 });
		tmp.push_back({ y8, x8 });
		tmp.push_back({ y9, x9 });

		for (int i = 0; i < 9; i++) {
			int ny = tmp[i].first;
			int nx = tmp[i].second;

			int new_sand = (map[r2][c2] * percent[i]) / 100;

			if (is_in_map(ny, nx) == false) {
				result += new_sand;
				basic_sand -= new_sand;
			}
			else {
				map[ny][nx] += new_sand;
				basic_sand -= new_sand;
			}
		}

		int alpha_y = tmp[9].first;
		int alpha_x = tmp[9].second;

		if (is_in_map(alpha_y, alpha_x) == false) {
			result += basic_sand;
		}
		else {
			map[alpha_y][alpha_x] += basic_sand;
		}

		map[r2][c2] = 0;
	}
	else if (dir == 2) {
		y0 = r2 + 1; x0 = c2 + 1; y1 = r2 + 1; x1 = c2 - 1;
		y2 = r2; x2 = c2 + 1; y3 = r2; x3 = c2 - 1;
		y4 = r2; x4 = c2 + 2; y5 = r2; x5 = c2 - 2;
		y6 = r2 - 1; x6 = c2 - 1; y7 = r2 - 1; x7 = c2 + 1;
		y8 = r2 - 2; x8 = c2;
		y9 = r2 - 1; x9 = c2;

		tmp.push_back({ y0, x0 });
		tmp.push_back({ y1, x1 });
		tmp.push_back({ y2, x2 });
		tmp.push_back({ y3, x3 });
		tmp.push_back({ y4, x4 });
		tmp.push_back({ y5, x5 });
		tmp.push_back({ y6, x6 });
		tmp.push_back({ y7, x7 });
		tmp.push_back({ y8, x8 });
		tmp.push_back({ y9, x9 });

		for (int i = 0; i < 9; i++) {
			int ny = tmp[i].first;
			int nx = tmp[i].second;

			int new_sand = (map[r2][c2] * percent[i]) / 100;

			if (is_in_map(ny, nx) == false) {
				result += new_sand;
				basic_sand -= new_sand;
			}
			else {
				map[ny][nx] += new_sand;
				basic_sand -= new_sand;
			}
		}

		int alpha_y = tmp[9].first;
		int alpha_x = tmp[9].second;

		if (is_in_map(alpha_y, alpha_x) == false) {
			result += basic_sand;
		}
		else {
			map[alpha_y][alpha_x] += basic_sand;
		}

		map[r2][c2] = 0;
	}
	else if (dir == 3) {
		y0 = r2 - 1; x0 = c2 + 1; y1 = r2 - 1; x1 = c2 - 1;
		y2 = r2; x2 = c2 + 1; y3 = r2; x3 = c2 - 1;
		y4 = r2; x4 = c2 + 2; y5 = r2; x5 = c2 - 2;
		y6 = r2 + 1; x6 = c2 + 1; y7 = r2 + 1; x7 = c2 - 1;
		y8 = r2 + 2; x8 = c2;
		y9 = r2 + 1; x9 = c2;

		tmp.push_back({ y0, x0 });
		tmp.push_back({ y1, x1 });
		tmp.push_back({ y2, x2 });
		tmp.push_back({ y3, x3 });
		tmp.push_back({ y4, x4 });
		tmp.push_back({ y5, x5 });
		tmp.push_back({ y6, x6 });
		tmp.push_back({ y7, x7 });
		tmp.push_back({ y8, x8 });
		tmp.push_back({ y9, x9 });

		for (int i = 0; i < 9; i++) {
			int ny = tmp[i].first;
			int nx = tmp[i].second;

			int new_sand = (map[r2][c2] * percent[i]) / 100;

			if (is_in_map(ny, nx) == false) {
				result += new_sand;
				basic_sand -= new_sand;
			}
			else {
				map[ny][nx] += new_sand;
				basic_sand -= new_sand;
			}
		}

		int alpha_y = tmp[9].first;
		int alpha_x = tmp[9].second;

		if (is_in_map(alpha_y, alpha_x) == false) {
			result += basic_sand;
		}
		else {
			map[alpha_y][alpha_x] += basic_sand;
		}

		map[r2][c2] = 0;
	}
	return;
}

void move_tornado(int r, int c, int dir)
{
	// r,c : x 위치
	// dir : 토네이도 방향, 0,1,2,3 : 좌, 우, 상, 하

	// r2, c2 : y 위치
	int r2;
	int c2;

	switch (dir) {
	case 0:
		r2 = r;
		c2 = c - 1;
		break;
	case 1:
		r2 = r;
		c2 = c + 1;
		break;
	case 2:
		r2 = r - 1;
		c2 = c;
		break;
	case 3:
		r2 = r + 1;
		c2 = c;
		break;
	default:
		r2 = r;
		c2 = c;
		break;
	}

	if (r2 == r && c2 == c)
		return;

	if (is_in_map(r2, c2) == false)
		return;

	make_sand(r2, c2, dir);
}

pair<int, int> make_next_location(int r, int c, int dir)
{
	int nr = 0;
	int nc = 0;

	if(dir == 0){
		nr = r;
		nc = c - 1;
	}
	else if (dir == 1) {
		nr = r;
		nc = c + 1;
	}
	else if (dir == 2) {
		nr = r - 1;
		nc = c;
	}
	else if (dir == 3) {
		nr = r + 1;
		nc = c;
	}

	pair<int, int>p = { nr, nc };
	return p;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	int sy = n / 2;
	int sx = n / 2;

	int dir[4] = { 0, 3, 1, 2 }; // 좌 하 우 상
	int cnt = 0;
	bool fin = false;

	while (true) {

		cnt++;
		for (int i = 0; i < cnt; i++) {
			int d = dir[0];
			move_tornado(sy, sx, d);
			pair<int, int>next_location = make_next_location(sy, sx, d);
			sy = next_location.first;
			sx = next_location.second;

			if (sy == 0 && sx == 0) {
				fin = true;
				break;
			}
		}
		if (fin)
			break;

		for (int i = 0; i < cnt; i++) {
			int d = dir[1];
			move_tornado(sy, sx, d);
			pair<int, int>next_location = make_next_location(sy, sx, d);
			sy = next_location.first;
			sx = next_location.second;

			if (sy == 0 && sx == 0) {
				fin = true;
				break;
			}
		}
		if (fin)
			break;

		cnt++;
		for (int i = 0; i < cnt; i++) {
			int d = dir[2];
			move_tornado(sy, sx, d);
			pair<int, int>next_location = make_next_location(sy, sx, d);
			sy = next_location.first;
			sx = next_location.second;

			if (sy == 0 && sx == 0) {
				fin = true;
				break;
			}
		}
		if (fin)
			break;

		for (int i = 0; i < cnt; i++) {
			int d = dir[3];
			move_tornado(sy, sx, d);
			pair<int, int>next_location = make_next_location(sy, sx, d);
			sy = next_location.first;
			sx = next_location.second;

			if (sy == 0 && sx == 0) {
				fin = true;
				break;
			}
		}
		if (fin)
			break;
	}

	cout << result;
	return 0;
}