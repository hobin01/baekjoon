#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int>fix_num;
int dp[41];
// 해보면 피보나치로 점화식 나옴
// dp[n] = dp[n-1] + dp[n-2]
// dp[0] ~ dp[40] 까지 구해놓기
void init()
{
	cin >> n >> m;
	fix_num.resize(m + 2);
	fix_num[0] = 0;
	fix_num[m + 1] = n + 1;
	for (int i = 1; i <= m; i++) {
		cin >> fix_num[i];
	}
}

void fibo(int num) {
	dp[0] = 1;
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 3;
	for (int i = 4; i <= num; i++)
		dp[i] = dp[i - 1] + dp[i - 2];
}

int multiple(vector<int>& v) {
	int ret = 1;
	for (auto num : v)
		ret *= num;
	return ret;
}

int main()
{
	init();
	fibo(40);

	vector<int>v; // 사이에 있는 것들 경우의 수 다 곱하면 답
	for (int i = 0; i < fix_num.size() - 1; i++) {
		int start = fix_num[i];
		int last = fix_num[i + 1];
		int cnt = last - start - 1;
		if (cnt <= 0)
			continue;
		v.push_back(dp[cnt]);
	}

	cout << multiple(v);
}