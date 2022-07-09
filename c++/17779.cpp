#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 경계선 + 내부 = 5
// (r,c) = (행, 열)
// 1번 : 1 <= r < x + d1, 1 <= c <= y
// 2번 : 1 <= r <= x + d2, y < c <= N
// 3번 : x + d1 <= r <= N, 1 <= c < y - d1 + d2
// 4번 : x + d2 < r <= N, y - d1 + d2 <= c <= N
// 1 ~ 4 : 5번에서 남은 부분

// N <= 20
// 기준점으로부터 가로 세로 길이 1 <= d <= 19
// 최대 400개 점에 대해 경우의 수 약 400개
// 최대 경우의 수 : 16만개 => 인구 합 등 단순 계산 고려해도 브루트포스로 충분

int N;
int area[21][21];
int result[6];
int x, y;
int d1, d2;
bool check[21][21];
int whole; // 전체 인구수
int minimum; // 최소 차이

void init()
{
	cin >> N;
	whole = 0;
	minimum = 987654321; // 최대 인구수 40000
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> area[i][j];
			whole += area[i][j];
		}
	}
}

void reset(int r, int c, int dd1, int dd2) {
	memset(result, 0, sizeof(result));
	memset(check, false, sizeof(check));
	x = r;
	y = c;
	d1 = dd1;
	d2 = dd2;
	// 기준점
}

void getBoundary() {
	for (int i = 0; i <= d1; i++) {
		// 1번 경계
		int r = x + i;
		int c = y - i;
		check[r][c] = true;
	}

	for (int i = 0; i <= d2; i++) {
		// 2번 경계
		int r = x + i;
		int c = y + i;
		check[r][c] = true;
	}

	for (int i = 0; i <= d2; i++) {
		// 3번 경계
		int r = x + d1 + i;
		int c = y - d1 + i;
		check[r][c] = true;
	}

	for (int i = 0; i <= d1; i++) {
		// 4번 경계
		int r = x + d2 + i;
		int c = y + d2 - i;
		check[r][c] = true;
	}
}

void getFirst() {
	for (int r = 1; r < (x + d1); r++) {
		for (int c = 1; c <= y; c++) {
			if (check[r][c])
				break;
			result[1] += area[r][c];
		}
	}
}

void getSecond() {
	for (int r = 1; r <= (x + d2); r++) {
		for (int c = N; c > y; c--) {
			if (check[r][c])
				break;
			result[2] += area[r][c];
		}
	}
}

void getThird() {
	for (int r = N; r >= (x + d1); r--) {
		for (int c = 1; c < (y - d1 + d2); c++) {
			if (check[r][c])
				break;
			result[3] += area[r][c];
		}
	}
}

void getFourth() {
	for (int r = N; r > (x + d2); r--) {
		for (int c = N; c >= (y - d1 + d2); c--) {
			if (check[r][c])
				break;
			result[4] += area[r][c];
		}
	}
}

void getFifth() {
	result[5] = whole - (result[1] + result[2] + result[3] + result[4]);
}

void getMinimum() {
	// 최대 인구와 최소 인구 차이 구하기
	int maxPeople = 0;
	int minPeople = 987654321;

	for (int i = 1; i <= 5; i++) {
		if (maxPeople < result[i])
			maxPeople = result[i];
		if (minPeople > result[i])
			minPeople = result[i];
	}

	if (minimum > (maxPeople - minPeople)) {
		minimum = (maxPeople - minPeople);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			for (int dd1 = 1; dd1 <= N; dd1++) {
				for (int dd2 = 1; dd2 <= N; dd2++) {

					reset(r, c, dd1, dd2);

					if ((x + d1 + d2) > N)
						continue;
					if (1 > (y - d1))
						continue;
					if ((y + d2) > N)
						continue;

					getBoundary();
					getFirst();
					getSecond();
					getThird();
					getFourth();
					getFifth();

					getMinimum();
				}
			}
		}
	}

	cout << minimum;
}