#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

typedef long long ll;

int n;
vector<int>number;
ll dp[21];
ll possible[21]; // 숫자, 개수
ll res = 0;

void make_number()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		number.push_back(a);
	}
}

int main()
{
	make_number();
	memset(dp, 0, sizeof(dp));
	
	dp[number[0]] = 1;

	for (int i = 1; i < n - 2; i++) {

		int num = number[i];

		memset(possible, 0, sizeof(possible));
		for (int j = 0; j < 21; j++) {

			if (dp[j] > 0) {

				if ((j + num >= 0) && (j + num <= 20)) {
					possible[j + num] += dp[j];
				}
				if ((j - num >= 0) && (j - num <= 20)) {
					possible[j - num] += dp[j];
				}
			}
		}
		memcpy(dp, possible, sizeof(dp));
	}

	int final_num = number[n - 2];
	int result_num = number[n - 1];

	for (int i = 0; i < 21; i++) {
		if (dp[i] > 0) {
			if (i + final_num == result_num)
				res += dp[i];
			if (i - final_num == result_num)
				res += dp[i];
		}
	}

	cout << res;
}
