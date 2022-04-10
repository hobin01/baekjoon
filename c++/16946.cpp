#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>

using namespace std;

int n, m;
int map[1001][1001]; // 실제 맵
pair<int,int> zero_map[1001][1001]; // 0의 개수 카운트 할 맵 {구역 번호, 카운트}
vector<pair<int, int>>zero_vec; // 0으로 연결된 위치 개수 탐색용
bool visited[1001][1001]; // 0 탐색 여부 확인용

int result[1001][1001]; // 최종 결과

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 }; // 상하좌우

// 0으로 연결된 위치들의 개수 먼저 카운트 (매번 탐색이 아닌 한 번 탐색으로 다 복사)
// 1 위치에서 상하좌우 탐색하면서 0 있으면 그 값들 + 1 (자기 자신) % 10

void init()
{
	cin >> n >> m;
	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		for (int j = 0; j < m; j++) {
			if (s[j] == '0')
				map[i][j] = 0;
			else
				map[i][j] = 1;
		}
		s.clear();
	}
	memset(visited, false, sizeof(visited));
}

void countZeros()
{
	// bfs로 0 연결된 위치들 몇 개인지 카운트
	queue<pair<int, int>> q;

	int section = 0; 
	// 나중에 1 위치에서 상하좌우 탐색할 때 공통 영역이면 합하면 안 되는 거 체크용

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			q = queue<pair<int, int>>{};
			zero_vec.clear();
			section++;

			if (map[i][j] == 1)
				continue;
			if (visited[i][j] == true)
				continue;

			q.push({ i,j });
			visited[i][j] = true;

			while (!q.empty()) {
				pair<int, int>zero = q.front();
				q.pop();
				zero_vec.push_back(zero);

				for (int k = 0; k < 4; k++) {
					int ny = zero.first + dy[k];
					int nx = zero.second + dx[k];

					if (ny < 0 || ny >= n || nx < 0 || nx >= m)
						continue;
					if (visited[ny][nx] == true)
						continue;
					if (map[ny][nx] == 1)
						continue;

					q.push({ ny, nx });
					visited[ny][nx] = true;
				}
			}

			int zero_size = zero_vec.size();
			for (auto zero : zero_vec) {
				zero_map[zero.first][zero.second] = { section,zero_size };
			}
		}
	}
}

void getResult()
{
	// 1 위치에서 상하좌우 돌면서 0 이면 그 위치 값들 합 + 1
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0) {
				result[i][j] = 0;
				continue;
			}

			if (map[i][j] == 1) {
				int sum = 1;
				vector<int>section_check; // 상하좌우 구역 체크용

				for (int k = 0; k < 4; k++) {
					int ni = i + dy[k];
					int nj = j + dx[k];

					bool check = false;

					if (ni < 0 || ni >= n || nj < 0 || nj >= m)
						continue;

					if (map[ni][nj] == 0) {
						for (auto section : section_check) {
							if (section == zero_map[ni][nj].first){
								check = true;
								break; // 이미 체크 된 영역
							}
						}

						if (check == false) {
							section_check.push_back(zero_map[ni][nj].first);
							sum += zero_map[ni][nj].second;
						}
					}
				}
				section_check.clear();

				sum %= 10;
				result[i][j] = sum;
			}
		}
	}
}

void printResult()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << result[i][j];
		}
		cout << '\n';
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	countZeros();
	getResult();
	printResult();
}