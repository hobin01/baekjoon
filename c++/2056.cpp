#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int n;
int times[10001]; // 해당 작업 걸리는 시간
vector<int>PreWork[10001]; // [i]를 선행 작업으로 가지는 노드
int degree[10001]; // 그래프 차수

void init()
{
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int weight, pre_cnt; 
		// weight: 시간, pre_cnt : 선행 작업 개수
		
		cin >> weight;
		cin >> pre_cnt;

		times[i] = weight;

		degree[i] = pre_cnt;

		for (int j = 0; j < pre_cnt; j++) {
			int pre_work;
			cin >> pre_work;
			PreWork[pre_work].push_back(i);
		}
	}
}

int topology()
{
	int result = 987654321;

	// 우선순위 큐 : pair = {걸린 시간, 노드 번호}
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> >pq;
	
	// 차수 0인 것들 넣기
	for (int i = 1; i <= n; i++) {
		if (degree[i] == 0) {
			pq.push({ times[i], i });
		}
	}

	while (!pq.empty())
	{
		int w = pq.top().first;
		int node = pq.top().second;
		pq.pop();

		result = w;

		for (int i = 0; i < PreWork[node].size(); i++) {
			int nextnode = PreWork[node][i];
			degree[nextnode]--;

			if (degree[nextnode] == 0) {
				pq.push({ w + times[nextnode], nextnode });
			}
		}
	}

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	cout << topology();
}