#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

int mod = 1000000;

string crypto = "";
int dp[5001];

int main()
{
	cin >> crypto;
	memset(dp, 0, sizeof(dp));

	if (crypto[0] == '0')
	{
		cout << 0;
		return 0;
	}

	if (crypto.size() == 1)
	{
		cout << 1;
		return 0;
	}

	dp[0] = 1;
	dp[1] = 1;

	for (int i = 2; i <= crypto.size(); i++) {
		if (crypto[i - 1] != '0') {
			dp[i] += dp[i - 1] % mod;
			dp[i] = dp[i] % mod;
		}
		string s = crypto.substr(i - 2, 2);
		int val = stoi(s);
		if (val >= 10 && val <= 26) {
			dp[i] += dp[i - 2] % mod;
			dp[i] = dp[i] % mod;
		}
	}

	cout << dp[crypto.size()];
}