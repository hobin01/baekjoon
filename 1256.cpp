#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<string>
using namespace std;

int n, m, k;
string word = "";
int dp[101][101]; // dp[x][y] = x개의 a와 y개의 z로 만들 수 있는 경우의 수
int max_k = 1000000001; // k는 1,000,000,000 이하

// x개의 a, y개의 z로 만들 수 있는 경우는 
// (x-1개의 a, y개의 z) + (x개의 a, y-1개의 z)
// dp[x][y] = dp[x-1][y] + dp[x][y-1]
// a와z의 개수를 받음. 이로 만들 수 있는 문자열 개수
int possible_num(int num_a, int num_z)
{
	// a나 z 중 하나만 남으면 경우는 1개
	if (num_a == 0 || num_z == 0)
		return 1;

	if (dp[num_a][num_z] != -1)
		return dp[num_a][num_z];

	int first_case = possible_num(num_a - 1, num_z);
	int second_case = possible_num(num_a, num_z - 1);
	dp[num_a][num_z] = min(first_case + second_case, max_k);

	return dp[num_a][num_z];
}

// 정답 단어 만들기
// skip : 건너뛰어야 할 수
// prev_is_a : 맨 앞에 a가 붙을 때 경우의 수
// skip < prev_is_a : num_a-1개의 a와 num_z개의 z로 다시 skip만큼 실행
// 아닌 경우 : num_a개의 a와 num_z-1개의 z로 skip - prev_is_a만큼 실행

void make_word(int num_a, int num_z, int skip)
{
	if (num_a == 0) {
		for (int i = 0; i < num_z; i++)
			word += 'z';
		return;
	}
	if (num_z == 0) {
		for (int i = 0; i < num_a; i++)
			word += 'a';
		return;
	}

	int prev_is_a = possible_num(num_a - 1, num_z);

	if (skip < prev_is_a) {
		word += 'a';
		make_word(num_a - 1, num_z, skip);
	}
	else {
		word += 'z';
		make_word(num_a, num_z - 1, skip - prev_is_a);
	}

	return;
}

int main()
{
	cin >> n >> m >> k;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			dp[i][j] = -1;

	bool possible = true;
	int max_possible = possible_num(n, m);

	// k번째 이므로 k-1번 뒤의 녀석을 구해야함
	// k가 만들 수 있는 최대 경우보다 크면 안 구해도 됨
	if (k > max_possible) {
		possible = false;
		cout << -1;
	}
	else {
		make_word(n, m, k - 1);
		cout << word;
	}

}