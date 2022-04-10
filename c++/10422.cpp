#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int T, L;
unsigned long long mod = 1000000007;
unsigned long long dp[5001];

// 길이 Length인 가능한 괄호 개수 : dp
// 5천자리 괄호면 ((...5천자리...)),
// (2자리 괄호) * (4998자리 괄호) ~ (4998자리 괄호) * (2자리 괄호)
unsigned long long recur(int Length)
{
	// 통째로 감싸진 경우
	if (Length == 0)
		return 1;

	if (dp[Length] > 0)
		return dp[Length];

	for (int i = 2; i <= Length; i += 2)
	{
		dp[Length] += (recur(i - 2) * recur(Length - i));
		dp[Length] %= mod;
	}

	return dp[Length];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;
	while (T--) {
		cin >> L;
		if (L % 2 != 0)
			cout << 0 << '\n';
		else
			cout << recur(L) << '\n';
	}
}

