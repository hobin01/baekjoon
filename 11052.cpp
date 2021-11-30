#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int* price;
int* dp;

void init()
{
	cin >> n;
	price = (int*)malloc(sizeof(int) * (n + 1));
	dp = (int*)malloc(sizeof(int) * (n + 1));
	dp[0] = 0;

	for (int i = 1; i <= n; i++) {
		cin >> price[i];
		dp[i] = 0;
	}
}

int get_max_price(int num)
{
	int max_price = price[num];
	for (int i = num - 1; i >= (num / 2); i--) {
		max_price = max(max_price, dp[i] + dp[num - i]);
	}

	return max_price;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	for (int i = 1; i <= n; i++) {
		dp[i] = get_max_price(i);
	}

	cout << dp[n];

	free(price);
	free(dp);
}