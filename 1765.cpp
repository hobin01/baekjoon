#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

int n, m;
vector<int>fvec[1001]; // friend
vector<int>evec[1001]; // enemy
vector<int>team[1001]; // [idx] : idx와 팀인 애들
int result;

void init()
{
	cin >> n;
	cin >> m;
	for (int i = 1; i <= m; i++) {
		char relation;
		int p, q;
		cin >> relation >> p >> q;
		if (relation == 'F') {
			fvec[p].push_back(q);
			fvec[q].push_back(p);
		}
		else {
			evec[p].push_back(q);
			evec[q].push_back(p);
		}
	}
	result = 0;
}

void get_team_friend()
{
	for (int i = 1; i <= n; i++) {
		if (fvec[i].size() != 0) {
			team[i] = fvec[i];
		}
	}
}

void get_team_enemy()
{
	bool visited[1001];
	memset(visited, false, sizeof(visited));

	for (int node = 1; node <= n; node++) {
		if (evec[node].size() == 0)
			continue;

		for (auto enemy : evec[node]) {
			for (auto enemy_enemy : evec[enemy]) {
				if (visited[enemy_enemy] == true)
					continue;
				team[node].push_back(enemy_enemy);
			}
		}

		visited[node] = true;
	}
}

void get_result()
{
	get_team_friend();
	get_team_enemy();

	bool visited[1001];
	memset(visited, false, sizeof(visited));

	queue<int>q; // bfs로 팀 구하기용 큐

	for (int node = 1; node <= n; node++) {
		if (visited[node] == true)
			continue;

		q.push(node);
		visited[node] = true;

		while (!q.empty()) {
			int now_node = q.front();
			q.pop();

			for (auto next_node : team[now_node]) {
				if (visited[next_node] == true)
					continue;

				q.push(next_node);
				visited[next_node] = true;
			}
		}

		result++;
	}

	cout << result;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	get_result();
}