#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<set>

using namespace std;

int n;
int weight[10001];
vector<int>tree[10001];
bool check[10001];
int dp[10001][2];
vector<int>result; // 경로
bool check2[10001]; // 경로에서 이전 노드 연결 여부 확인

// 현재 노드가 독립집합 원소면 다음 노드는 무조건 안됨
// 현재 노드가 독립집합 원소 아니면 다음 노드는 상관 없음
// dp[i][0] : i가 독립집합 아닐 때, i를 루트로 하는 서브트리에서의 최댓값
// dp[i][1] : i가 독립집합 일 때, "
// dp[i][0] += max(dp[next][0], dp[next][1])
// dp[i][1] += dp[next][0]

void make_tree()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> weight[i];

		check[i] = false;
		check2[i] = false;

		dp[i][0] = 0;
		dp[i][1] = 0;
	}
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
}

void search(int node)
{
	check[node] = true;
	dp[node][0] = 0;
	dp[node][1] = weight[node];

	for (int i = 0; i < tree[node].size(); i++) {
		int next = tree[node][i];
		if (check[next] == false) {
			search(next);
			dp[node][0] += max(dp[next][0], dp[next][1]);
			dp[node][1] += dp[next][0];
		}
	}
}

// dp[node][1] > dp[node][0] 이면서 연결된 노드가 경로에 포함 안 되어있음
// 인수 : 현재 노드, 이전 노드
void path(int node, int prev)
{
	if (dp[node][1] > dp[node][0]) {
		if (check2[prev] == false) {
			result.push_back(node);
			check2[node] = true;
		}
	}

	for (int i = 0; i < tree[node].size(); i++) {
		int next = tree[node][i];
		if (next != prev)
			path(next, node);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_tree();
	search(1); // 루트 1로 잡음
	path(1, 1); // 루트 1의 부모 노드는 자기 자신으로 처리
	sort(result.begin(), result.end());

	cout << max(dp[1][0], dp[1][1]) << '\n';
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << ' ';
}