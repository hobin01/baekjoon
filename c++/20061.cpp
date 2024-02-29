#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// 게임 규칙
// 행 다 차면 행 사라지고, 사라진 만큼 그 위의 블록 내려옴
// 그리고 사라진 행만큼 점수 획득
// 0,1번째 행에 블록 쌓이면 맨 끝 행 그만큼 사라지고 또 내려옴
// 새 블록은 바닥 or 다른 블록 만날때까지 내려옴
// 행 다차기, 0,1번째에 블록 존재 동시에 발생 시, 점수 획득까지 먼저 수행 후 0,1번째 행 처리

// 출력 : 1. 최종 점수, 2. 파랑, 초록 칸에 남은 블록 수 합

// 파랑칸은 초록칸 y=-x 기준으로 접은 것과 동일
// 블록 모양만 y=-x 기준으로 접어서 옮기면 동일한 게임

int n;
int t, x, y;
bool green[6][4];
bool blue[6][4];
vector<pair<int, pair<int, int>>> blocks;
int score;
int remains;

// 필요한 값 초기화
void init()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> t >> y >> x;
		blocks.push_back({ t, { y, x } });
	}
	memset(green, false, sizeof(green));
	memset(blue, false, sizeof(blue));
	score = 0;
	remains = 0;
}

// 블록 내리기
void move_block(pair<int, pair<int, int>>& block, bool map[6][4]) 
{
	int top = 6;

	if (block.first != 2) {
		for (int i = 0; i < 6; i++) {
			if (map[i][block.second.second]) {
				top = i;
				break;
			}
		}
	}
	else{
		for (int i = 0; i < 6; i++) {
			if (map[i][block.second.second] || map[i][block.second.second + 1]) {
				top = i;
				break;
			}
		}
	}

	if (block.first == 1) {
		map[top - 1][block.second.second] = true;
	}
	else if (block.first == 2) {
		map[top - 1][block.second.second] = true;
		map[top - 1][block.second.second + 1] = true;
	}
	else if (block.first == 3) {
		map[top - 1][block.second.second] = true;
		map[top - 2][block.second.second] = true;
	}
}

// 다 찬 행 지우기
void clear_row(bool map[6][4]) 
{
	vector<int> rows;

	for (int i = 0; i < 6; i++) {
		bool chk = true;
		for (int j = 0; j < 4; j++) {
			if (!map[i][j]) {
				chk = false;
				break;
			}
		}

		if (chk) {
			rows.push_back(i);
		}
	}

	if (rows.empty())
		return;

	// 점수 획득
	int sc = rows.size();
	score += sc;

	// 해당 열 지우고 내리기 
	for (auto r : rows) {
		for (int i = 0; i < 4; i++) {
			map[r][i] = false;
		}
	}

	for (int i = rows[0] - 1; i >= 0; i--) {
		for (int j = 0; j < 4; j++) {
			if (map[i][j]) {
				map[i][j] = false;
				map[i + sc][j] = true;
			}
		}
	}
}

// 0,1번째 행 처리
void clear_shadow_row(bool map[6][4]) {
	int cnt = 0;

	for (int i = 0; i < 2; i++) {
		bool chk = false;
		for (int j = 0; j < 4; j++) {
			if (map[i][j]) {
				chk = true;
				break;
			}
		}

		if (chk)
			cnt++;
	}

	for (int i = 0; i < cnt; i++) {
		for (int j = 0; j < 4; j++) {
			map[5 - i][j] = false;
		}
	}

	for (int i = (5 - cnt); i >= 0; i--) {
		for (int j = 0; j < 4; j++) {
			if (map[i][j]) {
				map[i][j] = false;
				map[i + cnt][j] = true;
			}
		}
	}
}

void game()
{
	pair<int, pair<int, int>> greenBlock;
	pair<int, pair<int, int>> blueBlock;
	for (auto block : blocks) {
		greenBlock = block;

		if (block.first == 1) {
			blueBlock.first = 1;
		}
		else if (block.first == 2) {
			blueBlock.first = 3;
		}
		else if (block.first == 3) {
			blueBlock.first = 2;
		}
		blueBlock.second = { block.second.second, block.second.first };

		move_block(greenBlock, green);
		move_block(blueBlock, blue);

		clear_row(green);
		clear_row(blue);

		clear_shadow_row(green);
		clear_shadow_row(blue);
	}

	// 남은 블록 계산
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			if (green[i][j])
				remains++;
			if (blue[i][j])
				remains++;
		}
	}

	cout << score << '\n' << remains;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	init();
	game();
}