#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

int n, r, q;
vector<int>tree[100001];
int dp[100001]; // i번째 노드의 서브트리의 노드 수
bool check[100001];

void dfs(int node)
{
	check[node] = true;
	for (int i = 0; i < tree[node].size(); i++) {
		int next_node = tree[node][i];
		if (!check[next_node]) {
			dfs(next_node);
			dp[node] += dp[next_node];
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> r >> q;
	for (int i = 1; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
		dp[a] = 1;
		dp[b] = 1;
	}

	dfs(r);

	while (q--)
	{
		int node;
		cin >> node;
		cout << dp[node] << '\n';
	}
}