#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int max_dp[3];
int min_dp[3];
int num[3];
int n;
int tmp0, tmp1, tmp2;

int main()
{
	cin >> n;
	int a, b, c;
	cin >> a >> b >> c;
	max_dp[0] = a;
	min_dp[0] = a;
	max_dp[1] = b;
	min_dp[1] = b;
	max_dp[2] = c;
	min_dp[2] = c;

	for (int i = 1; i < n; i++)
	{
		int num0, num1, num2;
		cin >> num[0] >> num[1] >> num[2];

		tmp0 = max_dp[0];
		tmp1 = max_dp[1];
		tmp2 = max_dp[2];

		max_dp[0] = max(tmp0, tmp1) + num[0];
		max_dp[1] = max(max(tmp0, tmp1), tmp2) + num[1];
		max_dp[2] = max(tmp1, tmp2) + num[2];

		tmp0 = min_dp[0];
		tmp1 = min_dp[1];
		tmp2 = min_dp[2];

		min_dp[0] = min(tmp0, tmp1) + num[0];
		min_dp[1] = min(min(tmp0, tmp1), tmp2) + num[1];
		min_dp[2] = min(tmp1, tmp2) + num[2];
	}

	cout << max(max(max_dp[0], max_dp[1]), max_dp[2]) << ' ';
	cout << min(min(min_dp[0], min_dp[1]), min_dp[2]);
}