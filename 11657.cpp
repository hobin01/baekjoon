#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int n, m;
long long inf = 9223372036854775807; // 무한대 (long long max)
vector<long long>v; // 각 노드 최단 시간 (v[1] : 출발) 
vector<pair<pair<int, int>, int>>edge; // {{출발, 도착}, 가중치}
int check = 0;

void make_bus()
{
	cin >> n >> m;
	v.resize(n + 1, inf);
	while (m--) {
		int a, b, c;
		cin >> a >> b >> c;
		edge.push_back({ {a,b},c });
	}
}

void Bellman_Ford()
{
	// 1번 노드 0으로 
	// n-1 번 돌면서 계산 안 된 출발 노드 (inf) 넘어가기
	// 한 번이라도 계산된 출발 노드면 업데이트

	v[1] = 0;
	for (int i = 1; i <= (n - 1); i++) {
		for (int j = 0; j < edge.size(); j++) {
			int from = edge[j].first.first;
			int to = edge[j].first.second;
			int cost = edge[j].second;

			if (v[from] == inf)
				continue;
			if (v[to] > (v[from] + cost))
				v[to] = (v[from] + cost);
		}
	}

	// 모든 edge에 대해 한 번 더 탐색하면서 정상 그래프인지 판단
	// 해당 노드 값이 inf면 1번에서 출발하여 가는 경로 없음
	// 업데이트가 다시 일어나면 음의 사이클 존재 : 무한히 작아지므로 비정상 그래프

	for (int i = 0; i < edge.size(); i++) {
		int from = edge[i].first.first;
		int to = edge[i].first.second;
		int cost = edge[i].second;

		// from 노드 가는 경로 X
		if (v[from] == inf) 
			continue;

		// 비정상 그래프 : check = -1로 잡음
		if (v[to] > (v[from] + cost)) {
			check = -1;
			return;
		}
	}
}

int main()
{
	make_bus();
	if (n == 1)
	{
		cout << 0;
		return 0;
	}

	Bellman_Ford();

	if (check == -1)
	{
		cout << -1;
		return 0;
	}

	else {
		for (int i = 2; i <= n; i++) {
			if (v[i] == inf)
				cout << -1 << '\n';
			else
				cout << v[i] << '\n';
		}
	}
}