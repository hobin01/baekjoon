#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>

using namespace std;

int V, E;
int A, B;

vector<int> graph[10001];
vector<int> inv_graph[10001];

bool visited[10001]; // SCC 돌면서 노드 체크
stack<int> stk;
vector<vector<int>> result;
bool checked[10001]; // 아예 다른 그래프인지 여부 체크

void init()
{
	cin >> V >> E;

	while (E--) {
		cin >> A >> B;
		graph[A].push_back(B);
		inv_graph[B].push_back(A);
	}

	memset(visited, false, sizeof(visited));

	// 연결 요소 오름차순 정렬
	for (int i = 1; i <= V; i++) {
		sort(graph[i].begin(), graph[i].end());
		sort(inv_graph[i].begin(), inv_graph[i].end());
	}

	memset(checked, false, sizeof(checked));
}

void dfs(int node)
{
	visited[node] = true;

	for (auto num : graph[node]) {
		if (visited[num])
			continue;

		dfs(num);
	}

	stk.push(node);
}

void dfs_scc(int node, vector<int>& vec)
{
	visited[node] = true;
	vec.push_back(node);

	for (auto num : inv_graph[node]) {
		if (visited[num])
			continue;

		dfs_scc(num, vec);
	}

	checked[node] = true;
}

void SCC()
{
	memset(visited, false, sizeof(visited));

	vector<int> vec;

	while (!stk.empty()) {
		int start = stk.top();
		stk.pop();

		if (visited[start])
			continue;

		dfs_scc(start, vec);
		sort(vec.begin(), vec.end());
		result.push_back(vec);
		vec.clear();
	}
}

bool compare_vec(const vector<int>& v1, const vector<int>& v2)
{
	if (v1[0] < v2[0])
		return true;
	else
		return false;
}

void get_result()
{
	cout << result.size() << '\n';
	sort(result.begin(), result.end(), compare_vec);

	for (int i = 0; i < result.size(); i++) {
		for (auto num : result[i]) {
			cout << num << ' ';
		}
		cout << -1;
		if (i != result.size() - 1)
			cout << '\n';
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	for (int node = 1; node <= V; node++) {
		if (checked[node] || visited[node])
			continue;

		dfs(node);
	}

	SCC();

	get_result();
}