#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m, k;
vector<int>vec; // 친구비
int v, w;
vector<int>graph[10001]; // 친구 연결 그래프
bool visited[10001];
int result;

void fail()
{
	cout << "Oh no";
}

void init()
{
	cin >> n >> m >> k;
	vec.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		int num;
		cin >> num;
		vec[i] = num;
	}
	for (int i = 1; i <= m; i++) {
		cin >> v >> w;
		graph[v].push_back(w);
		graph[w].push_back(v);
	}
	memset(visited, false, sizeof(visited));
	result = 0;
}

// dfs 돌면서 기존 그래프에서 가장 작은 값 구하기
// 그 합이 k 이하면 그게 정답, 아니면 fail

int dfs(int node, int minimum)
{
	visited[node] = true;

	for (auto next_node : graph[node]) {
		if (visited[next_node] == true)
			continue;

		minimum = dfs(next_node, min(minimum, vec[next_node]));
	}

	return min(minimum, vec[node]);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	int minimum = 100000000;

	for (int node = 1; node <= n; node++) {
		if (visited[node] == true)
			continue;
		result += dfs(node, minimum);
	}

	if (result > k)
		fail();
	else
		cout << result;
}