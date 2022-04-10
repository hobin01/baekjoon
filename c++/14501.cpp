#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

int n;
int res;
int dp[16];
int time[16];
int salary[16];

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int t, p;
		cin >> t >> p;
		time[i] = t;
		salary[i] = p;
	}

	memset(dp, 0, sizeof(dp));

	for (int i = 1; i <= n + 1; i++)
	{
		int t;
		int last;
		t = time[i];
		last = t + i;

		if (last > (n + 1))
			continue;

		for (int j = last; j <= n + 1; j++)
			dp[j] = max(dp[j], dp[i] + salary[i]);
	}

	cout << dp[n + 1];
}