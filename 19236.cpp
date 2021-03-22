#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

// 물고기 구조체, 위치, 방향, 살았는지 유무
struct fish {
	int y;
	int x;
	int dir;
	bool live;
};

int result = 0;
int aqua[4][4]; // 물고기 번호 저장
fish fishes[17]; // 물고기 정보 배열 (1~16)

// 원래 위치 + 8방향 (1~8번)
int dy[9] = { 0,-1,-1,0,1,1,1,0,-1 };
int dx[9] = { 0,0,-1,-1,-1,0,1,1,1 };

// 물고기 만들기
void make_aquarium()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			int a, b;
			cin >> a >> b;
			aqua[i][j] = a;
			fishes[a] = { i,j,b,true };
		}
	}
}

// dfs 돌기 전 기존 물고기 정보 저장
void copying(int new_map[][4], int exist_map[][4], fish new_fish[], fish exist_fish[])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			new_map[i][j] = exist_map[i][j];
		}
	}

	for (int i = 1; i <= 16; i++) {
		new_fish[i] = exist_fish[i];
	}
}

// 물고기 자리 바꿈
void swap_fish(int num1, int num2)
{
	fish tmp = fishes[num1];

	fishes[num1].y = fishes[num2].y;
	fishes[num1].x = fishes[num2].x;

	fishes[num2].y = tmp.y;
	fishes[num2].x = tmp.x;
}

// 물고기 이동
void move_fish()
{
	for (int i = 1; i <= 16; i++) {
		if (fishes[i].live == false)
			continue;

		int y = fishes[i].y;
		int x = fishes[i].x;
		int dir = fishes[i].dir;

		int ny = y + dy[dir];
		int nx = x + dx[dir];

		bool flag = false; // 현재 진행 방향으로 이동 가능한지 판단

		// 기존 방향으로 이동 가능한 경우
		if (ny >= 0 && ny < 4 && nx >= 0 && nx < 4) {

			// 빈 칸인 경우
			if (aqua[ny][nx] == 0) {
				flag = true;
				fishes[i].y = ny;
				fishes[i].x = nx;
				aqua[ny][nx] = i;
				aqua[y][x] = 0;
			}

			// 상어 아닌 경우
			else if (aqua[ny][nx] != -1) {
				flag = true;
				swap_fish(i, aqua[ny][nx]);
				swap(aqua[y][x], aqua[ny][nx]);
			}
		}

		// 방향 회전해서 찾아야하는 경우
		if (flag == false)
		{
			int ndir = dir + 1;
			if (ndir == 9)
				ndir = 1;
			int ny = y + dy[ndir];
			int nx = x + dx[ndir];

			// 원래 위치로 안 올 때까지
			while (ndir != dir)
			{
				if (ny >= 0 && ny < 4 && nx >= 0 && nx < 4) {

					// 빈 칸인 경우
					if (aqua[ny][nx] == 0) {
						fishes[i].y = ny;
						fishes[i].x = nx;
						aqua[ny][nx] = i;
						aqua[y][x] = 0;
						fishes[i].dir = ndir;
						break;
					}

					// 상어 아닌 경우
					else if (aqua[ny][nx] != -1) {
						swap_fish(i, aqua[ny][nx]);
						swap(aqua[y][x], aqua[ny][nx]);
						fishes[i].dir = ndir;
						break;
					}
				}

				ndir++;
				if (ndir == 9)
					ndir = 1;
				ny = y + dy[ndir];
				nx = x + dx[ndir];
			}
		}
	}
}

// 기존 물고기들로 변경 또는 상어가 먹은 걸 진행
void make_state(int y, int x, int ny, int nx, int fish_num, bool change)
{
	// 상어가 물고기 먹은 경우
	if (change == true) {
		aqua[y][x] = 0;
		aqua[ny][nx] = -1;
		fishes[fish_num].live = false;
	}

	// 직전 상태
	else {
		aqua[y][x] = -1;
		aqua[ny][nx] = fish_num;
		fishes[fish_num].live = true;
	}
}

// 상어가 (y,x)에 있을 때 dfs 실행
void dfs(int y, int x, int dir, int sum)
{
	result = max(result, sum);

	// 기존 상태 저장용
	int copy_aqua[4][4];
	fish copy_fishes[17];
	copying(copy_aqua, aqua, copy_fishes, fishes);

	move_fish();

	for (int idx = 1; idx <= 3; idx++) {
		int ny = y + dy[dir] * idx;
		int nx = x + dx[dir] * idx;

		if (ny >= 0 && ny < 4 && nx >= 0 && nx < 4) {
			if (aqua[ny][nx] == 0)
				continue;

			int fish_num = aqua[ny][nx];
			int ndir = fishes[fish_num].dir;

			// 상어가 (ny,nx) 먹은 경우 dfs 실행
			make_state(y, x, ny, nx, fish_num, true);
			dfs(ny, nx, ndir, sum + fish_num);
			// 지나간 경우 원래대로 돌리기
			make_state(y, x, ny, nx, fish_num, false);
		}
		else
			break;
	}

	// 기존 상태로 되돌리기
	copying(aqua, copy_aqua, fishes, copy_fishes);
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_aquarium();

	// (0,0) 먹은 뒤부터 계산
	int first_fish = aqua[0][0];
	int dir = fishes[first_fish].dir;
	fishes[first_fish].live = false;
	aqua[0][0] = -1;

	// dfs 진행
	dfs(0, 0, dir, first_fish);
	cout << result;
}