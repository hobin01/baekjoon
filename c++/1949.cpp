#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>

using namespace std;

int n;
int people[10001];
vector<int>town[10001];
int dp[10001][2];
bool check[10001];

void make_town()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> people[i];
		check[i] = false;
		dp[i][1] = 0;
		dp[i][0] = 0;
	}
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		town[a].push_back(b);
		town[b].push_back(a);
	}
}

// 현재 노드가 우수마을이면 다음 마을은 무조건 안 됨
// 현재 노드가 우수마을 아니면 다음 마을은 상관 없음
// dp[i][0] : i번 마을이 우수마을 아닐때 최대값
// dp[i][1] : i번 마을이 우수마을 일때 최댓값
// dp[i][0] = dp[i][0] + max(dp[next][0], dp[next][1])
// dp[i][1] = dp[i][1] + dp[next][0]
// 최댓값을 구하는 것이므로 세 마을 연속 선정 안되는 경우 없음
void dfs(int node)
{
	// 선정되었을 때 안 되었을 때 기본값
	dp[node][0] = 0;
	dp[node][1] = people[node];
	check[node] = true;

	for (int i = 0; i < town[node].size(); i++) {
		int next = town[node][i];
		if (check[next] == false) {
			dfs(next);
			dp[node][0] += max(dp[next][0], dp[next][1]);
			dp[node][1] += dp[next][0];
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_town();
	int root = 1; // 트리이므로 편의상 1을 루트로 잡음
	dfs(root);

	cout << max(dp[root][0], dp[root][1]);
}


