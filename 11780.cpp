#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<string>

using namespace std;

int n, m;
int dist[101][101]; // [i][j] : i to j 최소 비용
vector<int> station[101][101]; // [i][j] : i to j 거쳐가는 곳
int inf = 987654321;

void init()
{
	cin >> n;
	cin >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dist[i][j] = inf;
		}
	}

	for (int i = 1; i <= m; i++) {
		int a, b, c; // a to b , cost
		cin >> a >> b >> c;
		if (dist[a][b] != inf) {
			if (dist[a][b] > c) {
				dist[a][b] = c;
			}
		}
		else {
			dist[a][b] = c;
			station[a][b].push_back(a);
			station[a][b].push_back(b);
		}
	}
}

void Floyd_Warshall()
{
	// i : 중간 노드, j :  출발 노드, k : 도착 노드
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {

				// 시작, 끝 같은 경우 없음.
				if (j == k) {
					continue;
				}

				if ((dist[j][i] + dist[i][k]) < dist[j][k]) {
					dist[j][k] = dist[j][i] + dist[i][k];
					vector<int> v;
					v = station[j][i];
					for (int s = 1; s < station[i][k].size(); s++) {
						v.push_back(station[i][k][s]);
					}
					station[j][k] = v;
				}
			}
		}
	}
}

void print_dist()
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (dist[i][j] == inf) {
				cout << 0 << ' ';
			}
			else {
				cout << dist[i][j] << ' ';
			}
		}
		cout << '\n';
	}
}

void print_station()
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (dist[i][j] == inf) {
				cout << 0 << '\n';
			}
			else {
				cout << station[i][j].size() << ' ';
				for (int k = 0; k < station[i][j].size(); k++) {
					cout << station[i][j][k] << ' ';
				}
				cout << '\n';
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	Floyd_Warshall();

	print_dist();
	print_station();
}