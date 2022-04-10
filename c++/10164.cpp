#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

int N, M, K;
int r, c; // 동그라미 위치, (1,1)부터 시작
int result = 0;
int path[16][16];

void init()
{
	cin >> N >> M >> K;
	memset(path, 0, sizeof(path));

	if (K != 0) {
		r = K / M + 1;
		c = K % M;

		if (c == 0) {
			r -= 1;
			c = M;
		}
	}
	else {
		r = 0;
		c = 0;
	}

	// 시작부분 1로 채우기
	for (int i = 1; i <= N; i++) {
		path[i][1] = 1;
	}
	for (int i = 1; i <= M; i++) {
		path[1][i] = 1;
	}
}

// 격자점 길찾기와 동일한 문제
// 동그라미는 반드시 거쳐가는 곳
// 동그라미 있으면 1,1부터 동그라미까지 길찾기
// 동그라미부터 N,M 까지 길찾기 다시 시작
// 동그라미 없으면 1,1부터 N,M까지 길찾기

// 동그라미 없는 경우
int dp1(int n, int m)
{
	if (n == 1 || m == 1) {
		return 1;
	}

	for (int i = 2; i <= n; i++) {
		for (int j = 2; j <= m; j++) {
			path[i][j] = path[i - 1][j] + path[i][j - 1];
		}
	}

	return path[n][m];
}

// 동그라미 있는 경우
int dp2(int n, int m, int r, int c)
{
	if (n == 1 || m == 1)
		return 1;

	for (int i = 2; i <= r; i++) {
		for (int j = 2; j <= c; j++) {
			path[i][j] = path[i - 1][j] + path[i][j - 1];
		}
	}

	for (int i = r; i <= n; i++) {
		path[i][c] = path[r][c];
	}
	for (int i = c; i <= m; i++) {
		path[r][i] = path[r][c];
	}

	for (int i = r + 1; i <= n; i++) {
		for (int j = c + 1; j <= m; j++) {
			path[i][j] = path[i - 1][j] + path[i][j - 1];
		}
	}

	return path[n][m];
}

int main()
{
	init();
	if (r == 0 && c == 0) {
		cout << dp1(N, M);
	}
	else {
		cout << dp2(N, M, r, c);
	}
}