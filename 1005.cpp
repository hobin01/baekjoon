#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int T, n, k, w;
int weight[1001]; // 각 노드 가중치 저장, 0으로 초기화
vector<int>v[1001]; // i를 짓고 지어질 노드 저장
int result[1001]; // 각 노드의 가능한 최솟값, 루트는 자기 자신으로
int degree[1001]; // 각 노드의 차수 (fan-in)

// 위상 정렬 이용
// 상위 노드 중 완료된 것 + 자신의 가중치의 최댓값을 구하면 됨
// result[next] = max(result[next], result[node]+weight[next])
// node는 차수 0인 노드, next는 node의 자식 노드
void init()
{
	cin >> n >> k;
	for (int i = 0; i <= 1000; i++) {
		weight[i] = 0;
		v[i].clear();
		result[i] = 0;
		degree[i] = 0;
	}
	for (int i = 1; i <= n; i++)
		cin >> weight[i];
	for (int i = 0; i < k; i++) {
		int prev, next;
		cin >> prev >> next;
		v[prev].push_back(next);
		degree[next]++;
	}
	cin >> w;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;
	while (T--) {
		// 초기화
		init();

		// 선행 시행이 없는 노드들 q에 넣음
		queue<int>q;
		for (int i = 1; i <= n; i++) {
			if (degree[i] == 0) {
				q.push(i);
				result[i] = weight[i];
			}
		}

		// 위상정렬 수행
		while (!q.empty()) {
			int node = q.front();
			q.pop();

			if (node == w)
				break;

			for (int i = 0; i < v[node].size(); i++) {
				int next = v[node][i];
				result[next] = max(result[next], result[node] + weight[next]);

				degree[next]--;
				if (degree[next] == 0)
					q.push(next);
			}
		}

		cout << result[w] << '\n';
	}
}