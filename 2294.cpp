#include<iostream>
#include<algorithm>

using namespace std;

int n, k;
int coin[101];
int dp[100001];


int main()
{
	cin >> n >> k;
	
	int inf = 987654321;
	for (int i = 0; i <= k; i++)
		dp[i] = inf;

	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		coin[i] = num;
		dp[num] = 1;
	}

	for (int i = 0; i < n; i++) {
		for (int j = coin[i]; j <= k; j++) {
			if (j + coin[i] > k)
				break;
			dp[j + coin[i]] = min(dp[j + coin[i]], dp[j] + 1);
		}
	}

	if (dp[k] == inf)
		cout << -1;
	else
		cout << dp[k];
}