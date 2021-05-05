#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

// 주사위
int dice[10];
// 전체 맵 map[21]=end
int map[40];
// 해당 칸에 말 여부
bool check[40];
// 파란 칸에서 회전하는 경우 체크
int turn[40];
// 말의 위치
int horse[4];
// 점수
int score[40];
// 최종 점수
int result = 0;

void init()
{
	for (int i = 0; i < 10; i++)
		cin >> dice[i];
	memset(check, false, sizeof(check));
	
	for (int i = 0; i < 21; i++)
		map[i] = i + 1;
	map[21] = 21; // 도착 지점
	for (int i = 22; i < 27; i++)
		map[i] = i + 1;
	map[28] = 29;
	map[29] = 30;
	map[30] = 25;
	map[31] = 32;
	map[32] = 25;
	map[27] = 20;

	turn[5] = 22;
	turn[10] = 31;
	turn[15] = 28;
	turn[25] = 26;

	for (int i = 0; i < 21; i++)
		score[i] = i * 2;
	score[22] = 13;
	score[23] = 16;
	score[24] = 19;
	score[31] = 22;
	score[32] = 24;
	score[28] = 28;
	score[29] = 27;
	score[30] = 26;
	score[25] = 25;
	score[26] = 30;
	score[27] = 35;
}

void dfs(int cnt, int sum)
{
	if (cnt == 10) {
		result = max(result, sum);
		return;
	}

	for (int i = 0; i < 4; i++) {

		// 말의 현재 위치, 이동할 위치
		// 우선 현재 위치와 동일시하게 하여 파란칸인지 체크후 이동
		int now = horse[i];
		int next = horse[i];

		// 이동 횟수
		int move_count = dice[cnt];

		// 파란 칸인 경우
		if (turn[now] != 0) {
			next = turn[now];
			move_count--;
		}

		// 이동
		while (move_count--) {
			next = map[next];
		}

		// 아직 도착 안 했지만 다른 말이 있는 경우
		if (next != 21 && check[next])
			continue;

		check[now] = false;
		check[next] = true;
		horse[i] = next;

		dfs(cnt + 1, sum + score[next]);

		check[now] = true;
		check[next] = false;
		horse[i] = now;
	}
}

int main()
{
	init();
	dfs(0, 0);
	cout << result;
}