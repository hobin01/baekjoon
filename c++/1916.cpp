#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int n, m;
vector<pair<int, int>>v[1001]; // [i] : 출발, {도착, 가중치}
int dist[1001];
int From, To;

void make_map()
{
	cin >> n;
	cin >> m;

	for (int i = 0; i < m; i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		v[from].push_back({ to,weight });
	}
	cin >> From >> To;

	// 다익스트라 : 처음 모두 inf로 초기화
	for (int i = 1; i <= n; i++)
		dist[i] = 987654321;
}

// 우선순위 큐 이용한 다익스트라
void dijkstra(int start)
{
	dist[start] = 0; // 시작점은 0으로 초기화
	// 기본 오름차순, 가중치 작은 순으로 계산하므로
	// 음의 가중치 넣어야 함
	priority_queue<pair<int, int>>pq; // {가중치, 노드}
	pq.push({ 0,start });

	while (!pq.empty())
	{
		int d = (-1) * pq.top().first; // 가중치 양수로 변환
		int current = pq.top().second;
		pq.pop();

		// 계산된 경로가 지금 꺼낸 경로보다 작으면 계산할 필요 없음
		if (dist[current] < d)
			continue;

		// 가능한 경로 검사
		for (int i = 0; i < v[current].size(); i++) {
			int next = v[current][i].first;
			int next_d = d + v[current][i].second;

			// 경로 갱신
			if (dist[next] > next_d) {
				dist[next] = next_d;
				pq.push({ (-1) * next_d, next });
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_map();
	dijkstra(From);
	cout << dist[To];
}