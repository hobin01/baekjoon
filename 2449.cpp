#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n, k;
vector<int>vec;
int dp[201][201]; // dp[n][k] : n ~ k 번째 전구까지 최소 변환 횟수
int inf = 987654321;

void init()
{
	cin >> n >> k;
	vec.resize(n, 0);
	for (int i = 0; i < n; i++) {
		cin >> vec[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dp[i][j] = -1;
		}
	}
}

int calculate(int start, int last)
{
	// 동일 전구
	if (start == last)
		return 0;

	// 이미 계산된 범위
	if (dp[start][last] != -1)
		return dp[start][last];

	// start to last 최소 범위 계산 시작
	dp[start][last] = inf;

	for (int i = start; i < last; i++) {

		// 다른 색 전구나오는 경우
		int tmp = 0;
		if (vec[start] != vec[i + 1])
			tmp = 1;

		// start to i 최솟값
		int start_to_i = calculate(start, i);
		// i+1 to last 최솟값
		int i_plus_one_to_last = calculate(i + 1, last);

		// start to last의 최솟값은 min(원래값, start to i 최솟값 + i+1 to last 최솟값 + start 와 i+1 사이에 전구 색 바뀌는 지 여부 (0,1)
		dp[start][last] = min(dp[start][last], start_to_i + i_plus_one_to_last + tmp);
	}

	return dp[start][last];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	cout << calculate(0, n - 1);
}