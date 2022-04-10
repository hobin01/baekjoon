#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };
int n, m;
int map[51][51];
vector<pair<int, int>>virus;
int hole;
vector<vector<int>>virus_comb; // virus의 index 저장

// 시작
// 벽은 방문했다고 가정
void init()
{
	hole = 0;

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			
			if (map[i][j] == 2) {
				virus.push_back({ i,j });
			}

			if(map[i][j] == 0){
				hole++;
			}
		}
	}
}

// 활성 바이러스 위치 조합
// 바이러스는 최대 10개, 활성 최대 10개 => 10C5가지 최대 경우
void combination(vector<int>& arr, vector<int>& comb, int r, int idx, int depth)
{
	if (r == 0) {
		virus_comb.push_back(comb);
	}

	else if (depth == arr.size())
		return;

	else {
		comb[idx] = arr[depth];
		combination(arr, comb, r - 1, idx + 1, depth + 1);
		combination(arr, comb, r, idx, depth + 1);
	}
}

void make_active_virus()
{
	int virus_size = virus.size();
	vector<int>arr(virus_size);
	for (int i = 0; i < virus_size; i++)
		arr[i] = i;

	int r = m;
	vector<int>comb(r);
	int idx = 0;
	int depth = 0;

	combination(arr, comb, r, idx, depth);
}

int bfs(vector<int>& active)
{
	// 방문 기록 초기화
	bool visited[51][51];
	memset(visited, false, sizeof(visited));

	// active : 활성 바이러스 위치
	// 우선순위 큐 오름차순으로
	// 마지막으로 퍼진 시간 = 바이러스 다 퍼진 시간
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>> >q;
	for (int i = 0; i < active.size(); i++) {
		int idx = active[i];
		visited[virus[idx].first][virus[idx].second] = true;
		q.push({ 0,virus[idx] });
	}

	// 새로 바이러스 침투한 곳 개수
	// hole과 일치해야 다 퍼진 것
	int new_virus = 0;
	int time = 0;

	while (!q.empty()) {
		int cnt = q.top().first;
		int y = q.top().second.first;
		int x = q.top().second.second;
		q.pop();

		if (new_virus == hole)
			break;

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			// 범위 밖 & 벽
			if (ny < 0 || ny >= n || nx < 0 || nx >= n || map[ny][nx] == 1)
				continue;

			// 비활성 바이러스
			if (!visited[ny][nx] && map[ny][nx] == 2) {
				visited[ny][nx] = true;
				q.push({ cnt + 1,{ny,nx} });
			}

			// 빈 공간
			if (!visited[ny][nx] && map[ny][nx] == 0) {
				visited[ny][nx] = true;
				q.push({ cnt + 1, {ny,nx} });
				new_virus++;
				// 다 차는 최대 시간
				time = max(time, cnt + 1);
			}
		}
	}

	if (new_virus == hole) {
		return time;
	}
	else {
		return -1;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	make_active_virus();

	int result = 987654321;
	bool check = false;

	for (int i = 0; i < virus_comb.size(); i++) {

		vector<int>active = virus_comb[i];

		int res = bfs(active);

		if (res != -1) {
			check = true;
			result = min(result, res);
		}
	}

	if (check) {
		cout << result;
	}
	else
		cout << -1;

}