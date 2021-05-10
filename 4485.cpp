#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

int problem_num = 0;
int n = 1;
int map[125][125];
int dijk[125][125];
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };
int inf = 987654321;

void init()
{
	memset(map, sizeof(map), 0);
	memset(dijk, sizeof(dijk), 0);
	problem_num++;

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			dijk[i][j] = inf;
		}
	}
}

// 다익스트라 알고리즘으로 dijk[n][n] 구하면 된다.
// n<=125 이므로 우선순위 큐 이용해서 하기
void dijkstra(int start_y, int start_x)
{
	// 우선순위 큐 : { (y,x)까지 비용, {y,x}}
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>> >q;
	q.push({ map[start_y][start_x], {start_y, start_x} });
	dijk[start_y][start_x] = map[start_y][start_x];

	while (!q.empty())
	{
		int cost = q.top().first;
		int y = q.top().second.first;
		int x = q.top().second.second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n)
				continue;

			if (dijk[ny][nx] > (cost + map[ny][nx])) {
				int new_cost = cost + map[ny][nx];
				q.push({ new_cost,{ny, nx} });
				dijk[ny][nx] = new_cost;
			}
		}
	}
}

void print_result()
{
	cout << "Problem " << problem_num << ": " << dijk[n - 1][n - 1] << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (1)
	{
		init();

		if (n == 0)
			break;

		dijkstra(0, 0);
		print_result();
	}
}
