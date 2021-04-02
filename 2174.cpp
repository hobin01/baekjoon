#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

struct info {
	int x;
	int y;
	int num;
	char dir;
};

int A, B;
int N, M;
info robot[101]; // i번 로봇 정보 : 현재 위치(x,y), 방향(dir)
int map[101][101]; // x,y 에 num 로봇 존재
bool check; // 진행 가능 여부

void crash_wall(int num)
{
	cout << "Robot " << num << " crashes into the wall";
	return;
}

void crash_robot(int num1, int num2)
{
	cout << "Robot " << num1 << " crashes into robot " << num2;
	return;
}

void success()
{
	cout << "OK";
	return;
}

void left(info& r)
{
	if (r.dir == 'N') {
		r.dir = 'W';
	}
	else if (r.dir == 'W') {
		r.dir = 'S';
	}
	else if (r.dir == 'S') {
		r.dir = 'E';
	}
	else if (r.dir == 'E') {
		r.dir = 'N';
	}
	return;
}

void right(info& r)
{
	if (r.dir == 'N') {
		r.dir = 'E';
	}
	else if (r.dir == 'W') {
		r.dir = 'N';
	}
	else if (r.dir == 'S') {
		r.dir = 'W';
	}
	else if (r.dir == 'E') {
		r.dir = 'S';
	}
	return;
}

void front(info& r)
{
	if (r.dir == 'N') {
		r.y += 1;
		if (r.y > B) {
			crash_wall(r.num);
			check = false;
			return;
		}
		else {
			if (map[r.x][r.y] != 0) {
				crash_robot(r.num, map[r.x][r.y]);
				check = false;
				return;
			}
			else {
				map[r.x][r.y] = r.num;
				map[r.x][r.y - 1] = 0;
			}
		}
	}

	else if (r.dir == 'W') {
		r.x -= 1;
		if (r.x < 1) {
			crash_wall(r.num);
			check = false;
			return;
		}
		else {
			if (map[r.x][r.y] != 0) {
				crash_robot(r.num, map[r.x][r.y]);
				check = false;
				return;
			}
			else {
				map[r.x][r.y] = r.num;
				map[r.x + 1][r.y] = 0;
			}
		}
	}

	else if (r.dir == 'S') {
		r.y -= 1;
		if (r.y < 1) {
			crash_wall(r.num);
			check = false;
			return;
		}
		else {
			if (map[r.x][r.y] != 0) {
				crash_robot(r.num, map[r.x][r.y]);
				check = false;
				return;
			}
			else {
				map[r.x][r.y] = r.num;
				map[r.x][r.y + 1] = 0;
			}
		}
	}

	else if (r.dir == 'E') {
		r.x += 1;
		if (r.x > A) {
			crash_wall(r.num);
			check = false;
			return;
		}
		else {
			if (map[r.x][r.y] != 0) {
				crash_robot(r.num, map[r.x][r.y]);
				check = false;
				return;
			}
			else {
				map[r.x][r.y] = r.num;
				map[r.x - 1][r.y] = 0;
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> A >> B;
	cin >> N >> M;
	memset(map, 0, sizeof(map));
	for (int i = 1; i <= N; i++) {
		int x, y;
		char dir;
		cin >> x >> y >> dir;
		robot[i].x = x;
		robot[i].y = y;
		robot[i].dir = dir;
		robot[i].num = i;
		map[x][y] = i;
	}
	
	check = true;

	for (int i = 1; i <= M; i++) {
		if (!check)
			break;

		int num;
		char command;
		int repeat;
		cin >> num >> command >> repeat;

		if (command == 'L') {
			while (repeat--) {
				if (!check)
					break;
				left(robot[num]);
			}
		}

		else if (command == 'R') {
			while (repeat--) {
				if (!check)
					break;
				right(robot[num]);
			}
		}

		else if (command == 'F') {
			while (repeat--) {
				if (!check)
					break;
				front(robot[num]);
			}
		}
	}

	if (check)
		success();
}