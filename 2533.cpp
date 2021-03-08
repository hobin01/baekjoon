#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

vector<int>tree[1000001]; // 원래 트리
vector<int>top_down[1000001]; // 부모->자식만 연결한 트리
int dp[1000001][2];
int n;

// 루트를 1번으로
void make_tree()
{
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		tree[u].push_back(v);
		tree[v].push_back(u);

		dp[i][0] = -1;
		dp[i][1] = -1;
	}

	dp[n][0] = -1;
	dp[n][1] = -1;
}

// root가 1일 때, parent 노드의 자식 노드 구하기
// 마지막에 free 시키기

// 부모 노드가 얼리어댑터면 자식은 상관 없음
// 부모가 얼리어댑터 아니면 자식은 무조건 얼리어댑터
// 이를 이용하기 위해 top_down 만듬
void make_top_down(int parent, int node)
{
	// parent : node의 부모노드
	for (int i = 0; i < tree[node].size(); i++) {
		int child = tree[node][i];
		if (child == parent)
			continue;
		top_down[node].push_back(child);
		make_top_down(node, child);
	}
}

// dp[i][0] : i번 노드가 얼리어댑터 아니고
// i번 노드가 root인 서브트리의 얼리어댑터 최솟값
// dp[i][1] : i번 노드가 얼리어댑터이고 서브트리의 얼리어댑터 최솟값
// dfs 이용해 
// dfs(parent, state) : state가 0이면 자식은 무조건 얼리어댑터이므로
// dp[parent][0] += dfs(childe,1) 을 child 만큼 dfs로 반복
// state가 1이면 자식은 상관없음
// dp[parent][1] += min(dfs(child,0), dfs(child,1)) 을 child 만큼 dfs 반복

int dfs(int parent, int state)
{
	// 리프 노드인 경우
	if (top_down[parent].empty()) {
		if (state == 0)
			return 0;
		else
			return 1;
	}

	// 서브트리에서 계산 완료된 경우
	if (dp[parent][state] != -1) {
		return dp[parent][state];
	}

	// 부모가 얼리어댑터 아닌 경우, 자식은 무조건 얼리어댑터
	if (state == 0) {
		dp[parent][state] = 0;
		for (int i = 0; i < top_down[parent].size(); i++) {
			dp[parent][state] += dfs(top_down[parent][i], 1);
		}
	}

	// 부모가 얼리어댑터인 경우, 자식은 상관없음 (min값)
	else {
		dp[parent][state] = 1;
		for (int i = 0; i < top_down[parent].size(); i++) {
			dp[parent][state] += min(dfs(top_down[parent][i], 0), dfs(top_down[parent][i], 1));
		}
	}

	return dp[parent][state];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_tree();
	make_top_down(1, 1);

	// 루트(1)가 얼리어댑터인 경우, 아닌 경우 중 최솟값이 정답
	int answer = min(dfs(1, 0), dfs(1, 1));
	cout << answer;
}


