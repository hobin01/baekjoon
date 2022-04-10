#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

int n;
vector<int>graph[101]; // 주어진 그래프
vector<int>inv_graph[101]; // 역방향 그래프
bool visited[101]; // SCC 돌면서 노드 체크용
stack<int>stk; // SCC에 필요한 스택
vector<int>result; 

// 주어진 입력이 1->a, 2->b, ... 순의 그래프로 생각
// SCC 이용해서 강연결 요소인 것들 전부 골라내면 최대로 뽑은 것

void init()
{
	cin >> n;
	int node;
	for (int i = 1; i <= n; i++) {
		cin >> node;
		graph[i].push_back(node);
		inv_graph[node].push_back(i);
	}

	memset(visited, false, sizeof(visited));

	// 연결 요소 오름차순
	for (int i = 1; i <= n; i++) {
		sort(graph[i].begin(), graph[i].end());
		sort(inv_graph[i].begin(), inv_graph[i].end());
	}
}

void dfs(int node)
{
	// dfs로 연결된 애들 탐색
	// 끝나는 순으로 스택에 넣기
	// node : 시작 정점

	visited[node] = true;

	for (auto next_node : graph[node]) {
		if (visited[next_node])
			continue;
		dfs(next_node);
	}
	stk.push(node);
}

void dfs_inv(int node, vector<int>& vec)
{
	// 스택 top부터 역방향 그래프에서 dfs 

	visited[node] = true;
	vec.push_back(node);

	for (auto next_node : inv_graph[node]) {
		if (visited[next_node])
			continue;
		dfs_inv(next_node, vec);
	}
}

void SCC()
{
	// 코사라주 알고리즘으로 SCC 구하기

	for (int node = 1; node <= n; node++) {
		if (visited[node])
			continue;
		dfs(node);
	}

	memset(visited, false, sizeof(visited));
	vector<int>vec; // 강연결요소 저장용

	while (!stk.empty()) {
		int start = stk.top();
		stk.pop();

		if (visited[start])
			continue;

		dfs_inv(start, vec);

		// vec 확인
		// 원소 2개 이상이면 scc
		// 1개인데 자기 자신 가리켜도 scc

		if (vec.size() >= 2) {
			for (auto num : vec) {
				result.push_back(num);
			}
		}
		if (vec.size() == 1) {
			int num = vec[0];
			if (graph[num][0] == num)
				result.push_back(num); // graph는 값 1개만 가짐
		}

		vec.clear();
	}

	// 결과는 오름차순
	sort(result.begin(), result.end());
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	SCC();

	cout << result.size() << '\n';

	for (auto num : result) {
		cout << num << '\n';
	}
}