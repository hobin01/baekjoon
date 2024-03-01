#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

// 규칙
// 택시 도착지 이동 시 연료 충전, 연료 바닥 시 끝
// 손님은 가장 가까운 거리 손님 태움
// 손님 우선순위
// 1. 거리
// 2. 행 번호 작은 순
// 3. 열 번호 작은 순
// 
// 손님, 택시 같은 위치면 거리 0
// 연료: 1칸 이동 시 1소모
// 성공적 도착 시 이동 시 소비된 연료 2배 충전
// 도착 시 연료 0되는 경우는 실패 X = > 연료 충전됨
// 
// 출력 : 최종 남은 연료 양
// - 1 : 중간에 멈춘 경우, 손님 다 못 옮기는 경우(벽에 둘러쌓인 등 택시 진입 불가)

int n, m, fuel;

struct info {
	bool wall; // 0, 1 
	int start; // 출발 번호
	vector<int> finishes; // 도착 번호
};

info map[21][21];
bool visited[21][21];
pair<int, int> taxi;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 }; // 상하좌우

void init()
{
	cin >> n >> m >> fuel;

	int wall;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> wall;
			map[i][j].wall = wall;
			map[i][j].start = 0;
			map[i][j].finishes.clear();
			visited[i][j] = false;
		}
	}

	int y, x;
	cin >> y >> x;
	taxi = { y, x };

	for (int i = 1; i <= m; i++) {
		cin >> y >> x;
		map[y][x].start = i;
		cin >> y >> x;
		map[y][x].finishes.push_back(i);
	}
}

bool get_customer()
{
	// 어느 위치에 있는 손님 태울 지 선택 
	vector<pair<int, pair<int, int>>> vec;

	// 우선순위 : 거리, 행 작은 값, 열 작은 값 순 
	// 거리, 위치 값
	queue<pair<int, pair<int, int>>> q;

	q.push({ 0, taxi });
	memset(visited, false, sizeof(visited));
	visited[taxi.first][taxi.second] = true;

	while (!q.empty()) {
		int d = q.front().first;
		int y = q.front().second.first;
		int x = q.front().second.second;

		q.pop();

		// 손님인 경우
		if (map[y][x].start > 0) {
			vec.push_back({ d, { y, x } });
		}

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny <= 0 || nx <= 0 || ny > n || nx > n)
				continue;

			if (map[ny][nx].wall)
				continue;

			if (visited[ny][nx])
				continue;

			visited[ny][nx] = true;
			q.push({ d + 1, { ny, nx } });
		}
	}

	// 손님 태울 수 없는 경우 
	if (vec.empty())
		return false;
	
	// 우선순위 : 거리, 행, 열 작은 순
	sort(vec.begin(), vec.end());

	// 택시 위치 업데이트
	taxi = vec[0].second;
	
	// 연료 계산
	fuel -= vec[0].first;

	// 연료 다 떨어짐 
	if (fuel <= 0) {
		return false;
	}

	return true;
}

bool put_customer()
{
	// 손님 도착지에 내려줌 
	bool res = false;

	// 거리, 위치 값
	queue<pair<int, pair<int, int>>> q;

	q.push({ 0, taxi });
	memset(visited, false, sizeof(visited));
	visited[taxi.first][taxi.second] = true;

	// 목표 지점 
	int target = map[taxi.first][taxi.second].start;

	// 태운 곳 0으로 초기화
	map[taxi.first][taxi.second].start = 0;

	while (!q.empty()) {
		int d = q.front().first;
		int y = q.front().second.first;
		int x = q.front().second.second;

		q.pop();

		// 목적지 도착한 경우 
		bool chk = false;
		for (auto v : map[y][x].finishes) {
			if (v == target) {
				chk = true;
				break;
			}
		}

		if (chk) {
			res = true;
			fuel -= d;
			taxi = { y, x };

			// 그 전에 연료 다 떨어졌던 경우
			if (fuel < 0) {
				res = false;
			} 
			// 연료 충전
			else {
				fuel += (2 * d);
			}

			break;
		}

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny <= 0 || nx <= 0 || ny > n || nx > n)
				continue;

			if (map[ny][nx].wall)
				continue;

			if (visited[ny][nx])
				continue;

			visited[ny][nx] = true;
			q.push({ d + 1, { ny, nx } });
		}
	}

	return res;
}

void game()
{
	bool res;
	for (int i = 0; i < m; i++) {
		res = get_customer();

		if (!res) {
			cout << -1;
			return;
		}

		res = put_customer();

		if (!res) {
			cout << -1;
			return;
		}
	}

	cout << fuel;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	init();
	game();
}