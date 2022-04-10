#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

int n;
// 주사위 마주보는 면 
// A-F, B-D, C-E

int dice[10001][6];
int other_side[6] = { 5,3,4,1,2,0 }; // 반대편 수

void init()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> dice[i][j];
		}
	}
}

int calculate(int up, int idx, int result)
{
	// up : 윗면 수, idx : idx번째 주사위 
	// A=0~F=5

	int max_num = 0;
	int down = other_side[up];

	if (idx == n - 1) {

		for (int i = 0; i < 6; i++) {
			if (i == up || i == down)
				continue;
			max_num = max(max_num, dice[n - 1][i]);
		}
		result += max_num;

		return result;
	}

	for (int i = 0; i < 6; i++) {
		if (i == up || i == down)
			continue;
		max_num = max(max_num, dice[idx][i]);
	}

	// 다음 주사위
	int up_num = dice[idx][up];
	int next_down = 0;
	for (int i = 0; i < 6; i++) {
		if (dice[idx + 1][i] == up_num) {
			next_down = i;
		}
	}
	int next_up = other_side[next_down];

	return calculate(next_up, idx + 1, result + max_num);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	int res = 0;
	for (int i = 0; i < 6; i++) {
		res = max(res, calculate(i, 0, 0));
	}

	cout << res;
}