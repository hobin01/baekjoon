#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

int n;
long long m;
vector<long long> distances;
vector<vector<pair<int, long long>>> weights;

void init()
{
	cin >> n >> m;
	distances.resize(n + 1, LLONG_MAX);
	weights.resize(n + 1, vector<pair<int, long long>>());

	int node1, node2;
	for (long long i = 1; i <= m; i++) {
		cin >> node1 >> node2;

		weights[node1].push_back({ node2, i });
		weights[node2].push_back({ node1, i });
	}
}

void dijkstra()
{
	distances[1] = 0LL;

	// 거리, 노드 번호
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>> > pq;
	pq.push({ 0, 1 });

	int node, next_node;
	long long dist, next_dist, tmp;

	while (!pq.empty()) {
		dist = pq.top().first;
		node = pq.top().second;
		pq.pop();

		for (auto w : weights[node]) {
			next_node = w.first;
			next_dist = w.second;

			if (next_dist < dist) {
				tmp = (dist - next_dist) / m;
				if ((dist - next_dist) % m)
					tmp++;
				next_dist += (m * tmp);
			}
			
			if (distances[next_node] > next_dist) {
				distances[next_node] = next_dist;
				pq.push({ distances[next_node] , next_node });
			}
		}
	}

	cout << distances[n];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	init();
	dijkstra();
}