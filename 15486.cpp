#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n, t, p;
int arr[1500002][2];
int dp[1500002];

void init()
{
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> t >> p;
		arr[i][0] = t;
		arr[i][1] = p;
	}
	memset(dp, 0, sizeof(dp));
}

// i 번 째 날 t 일 일 한 거 : i+t 일에 돈 들어온다고 생각
// dp[x] = max(dp[x], P_i + dp[i]) (i+t=x)
// n+1보다 큰 날은 계산 X

int getResult() {
	int result = 0;
	int current = 0; // 현재 날 까지 최대값

	for (int i = 1; i <= (n + 1); i++) {
		int T = arr[i][0];
		int P = arr[i][1];

		int x = i + T;
		current = max(current, dp[i]);
		if (x > (n + 1)) {
			result = max(result, current);
		}
		else {
			dp[x] = max(dp[x], P + current);
			result = max(result, current);
		}
	}

	return result;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	init();
	cout << getResult();
}