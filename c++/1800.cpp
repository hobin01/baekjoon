#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>

using namespace std;

int N, P, K;
vector<pair<int, int>>v[1001]; // i번 노드와 {node, w} 로 연결됨
int dist[1001]; // i번 노드까지 경로 중 가중치가 x 이하인 경로 수, k이하여야함

void init()
{
	cin >> N >> P >> K;
	for (int i = 0; i < P; i++) {
		int node1, node2, cost;
		cin >> node1 >> node2 >> cost;
		v[node1].push_back({ node2,cost });
		v[node2].push_back({ node1,cost });
	}
}

// N번 노드까지 도달할 때
// 가중치가 x 이하인 경로 수는 K보다 작아야한다.
// 다익스트라로 이를 판단
// x를 1~1,000,000 까지 돌리면서 이분 탐색으로 x 구하기

bool dijkstra(int x)
{
	for (int i = 0; i <= 1000; i++)
		dist[i] = 987654321;
	
	// 우선 순위 큐 : 오름차순으로 (top : 제일 작음)
	// pair<int,int> : 가중치(x 이하 간선 개수), 다음노드
	// 1번 노드가 인터넷 연결 => 1번부터 탐색
	// x보다 큰 가중치 갖는 경로만 +1 해준다
	// 마무리로 K와 비교해서 K 이하일 때만 이분탐색 진행
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > >pq;
	pq.push({ 0,1 });
	dist[1] = 0;

	while (!pq.empty()) {
		int cost = pq.top().first; // node까지의 위 조건 만족하는 길이
		int node = pq.top().second;

		pq.pop();

		// 큐에 넣을 때 길이는 +1 또는 같음. 원래 노드가 더 작은 값이면
		// 아래 과정 굳이 안해도 됨.
		if (dist[node] < cost)
			continue;

		for (int i = 0; i < v[node].size(); i++) {
			int next_node = v[node][i].first;
			int next_weight = v[node][i].second; // 간선 가중치
			int next_cost = cost;

			// x보다 큰 경우
			if (next_weight > x) {
				next_cost += 1;
			}
			
			// 경로 수 더 작은 값으로 업데이트
			if (next_cost < dist[next_node]) {
				dist[next_node] = next_cost;
				pq.push({ next_cost,next_node });
			}
		}
	}

	if (dist[N] <= K) 
		return true;
	
	else
		return false;
}

// 이분 탐색
// dijkstra값 true면 mid 까지는 통과됨 => right = mid-1
// false면 mid까지는 통과 안 됨 => left = mid+1
int binary_search(int left, int right)
{
	int result = -1;
	int mid = (left + right) / 2;
	while (left <= right) {
		mid = (left + right) / 2;
		if (dijkstra(mid)) {
			result = mid;
			right = mid - 1;
		}
		else
			left = mid + 1;
	}
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	cout << binary_search(0, 1000001);
}