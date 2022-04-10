#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

#define MAX 100000
int n, k;
int dp[100001]; 
bool check[100001];

// 초기화
void init()
{
	cin >> n >> k;
	memset(dp, 987654321, sizeof(dp));
	memset(check, false, sizeof(check));
}

// 방문한적 없으면 dp[new] = dp[now] or dp[now]+1
// 방문한적 있는데 새로운 결과가 더 작은 값이면
// 그 값으로 업데이트 후 queue에 넣기
void bfs()
{
	queue<int>q;
	q.push(n);
	check[n] = true;
	dp[n] = 0;

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		if ((now + 1 >= 0) && (now + 1 <= MAX)) {
			if (check[now + 1] == false) {
				q.push(now + 1);
				check[now + 1] = true;
				dp[now + 1] = dp[now] + 1;
			}
			else {
				if (dp[now + 1] > dp[now] + 1) {
					q.push(now + 1);
					dp[now + 1] = dp[now] + 1;
				}
			}
		}

		if ((now - 1 >= 0) && (now - 1 <= MAX)) {
			if (check[now - 1] == false) {
				q.push(now - 1);
				check[now - 1] = true;
				dp[now - 1] = dp[now] + 1;
			}
			else {
				if (dp[now - 1] > dp[now] + 1) {
					q.push(now - 1);
					dp[now - 1] = dp[now] + 1;
				}
			}
		}

		if ((2 * now >= 0) && (2 * now <= MAX)) {
			if (check[2 * now] == false) {
				q.push(2 * now);
				check[2 * now] = true;
				dp[2 * now] = dp[now];
			}
			else {
				if (dp[2 * now] > dp[now]) {
					q.push(2 * now);
					dp[2 * now] = dp[now];
				}
			}
		}
	}
}

int main()
{
	init();
	bfs();
	cout << dp[k];
}