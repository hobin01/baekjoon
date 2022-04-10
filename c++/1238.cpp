#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

#define INF 987654321
int n, m, x;
int dist[1001]; // 출발점에서 도착점까지 최소 거리
vector<pair<int, int>>v[1001]; // {연결 지점, 거리}
int go[1001]; // 파티 장소까지 i번에서 출발해서 갈 때 최솟값
int back[1001]; // 파티장소에서 i번으로 올 때 최솟값
int result;

// 다익스트라로 출발 -> 도착 최소 거리 구하고
// 다시 다익스트라로 도착 -> 출발 최소거리 구해서
// 합이 최대인 것이 정답

void dist_init()
{
	fill(dist, dist + 1001, INF);
}

void init()
{
	cin >> n >> m >> x;
	for (int i = 0; i < m; i++) {
		int Start, End, Cost;
		cin >> Start >> End >> Cost;
		v[Start].push_back({ End,Cost });
	}
	result = 0;
	dist_init();
}

void dijkstra(int start, int last)
{
	dist_init();

	// 우선순위 큐 : {거리, 다음 지점}, 큐에는 거리 오름차순으로 (top이 거리 제일 짧음)
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pq;
	pq.push({ 0,start });
	dist[start] = 0;

	while (!pq.empty())
	{
		int cost = pq.top().first; 
		int now = pq.top().second;
		pq.pop();

		for (int i = 0; i < v[now].size(); i++)
		{
			int ncost = v[now][i].second;
			int next = v[now][i].first;

			if (dist[next] > dist[now] + ncost) {
				dist[next] = dist[now] + ncost;
				pq.push({ ncost,next });
			}
		}
	}

	// 파티 장소에서 각 집으로 가는 경우
	if (last == -1) {
		for (int i = 1; i <= n; i++) {
			back[i] = dist[i];
		}
	}

	// 파티 장소로 가는 경우
	else
		go[start] = dist[last];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	// start부터 x까지 최소 거리 구하기
	for (int start = 1; start <= n; start++) {
		dijkstra(start, x);
	}

	// 돌아올 때 최소 거리 구하기
	dijkstra(x, -1);

	// 가장 오래 걸린 사람 구하기
	for (int i = 1; i <= n; i++) {
		if (i == x)
			continue;
		result = max(result, go[i] + back[i]);
	}

	cout << result;
}
