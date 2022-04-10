#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
#include<set>

using namespace std;

int n, m, D;
int map[16][16];
int copy_map[16][16];
vector<vector<int>>archer; // 3명의 궁수 위치 
int dy[3] = { 0,-1,0 };
int dx[3] = { -1,0,1 }; // 좌, 위, 우 방향만 탐색

// 처음 세팅
void init()
{
	cin >> n >> m >> D;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			copy_map[i][j] = map[i][j];
		}
	}
}

// 맵 원래대로 돌리기
void start()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			map[i][j] = copy_map[i][j];
}

// 거리구하기
int dist(int y1, int x1, int y2, int x2)
{
	return abs(y1 - y2) + abs(x1 - x2);
}

// 궁수 위치 조합 구하기
void combination(vector<int>arr, vector<int>comb, int r, int idx, int depth)
{
	// r개 뽑은 경우
	if (r == 0) 
		archer.push_back(comb);
	// r개 다 못 채운 경우
	else if (depth == arr.size())
		return;
	else {
		// arr[depth] 뽑은 경우
		comb[idx] = arr[depth];
		combination(arr, comb, r - 1, idx + 1, depth + 1);
		// 안 뽑은 경우
		combination(arr, comb, r, idx, depth + 1);
	}
}

// 공격 받을 적 위치 찾기, p:궁수 위치
pair<int, int> enemy(pair<int, int>p)
{
	pair<int, int>attacked = { 987654321,987654321 };
	int min_d = D; // 공격 받는 적 최소 거리용
	bool visited[16][16];
	memset(visited, false, sizeof(visited));
	
	// 우선 순위 큐 오름차순으로 
	priority_queue < pair<int, pair<int, int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>> >q;
	q.push({ 1,{p.first - 1,p.second} }); // 궁수 바로 앞부터 탐색
	visited[p.first - 1][p.second] = true;

	while (!q.empty())
	{
		int d = q.top().first;
		int y = q.top().second.first;
		int x = q.top().second.second;
		q.pop();

		if (d > D)
			continue;

		if (map[y][x] == 1) {
			if (min_d < d)
				continue;
			else if (min_d == d) {
				if (attacked.second > x) {
					attacked.first = y;
					attacked.second = x;
				}
			}
			else {
				attacked.first = y;
				attacked.second = x;
				min_d = d;
			}
		}

		for (int i = 0; i < 3; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			int nd = d + 1;

			if (ny >= 0 && ny < n && nx >= 0 && nx < m) {
				if (visited[ny][nx] == false && nd <= D) {
					visited[ny][nx] = true;
					q.push({ nd,{ny,nx} });
				}
			}
		}
	}

	// attacked로 안 되는 값이 들어오는 경우 : 체크 되는 경우는 없을 듯
	if (attacked.first != 987654321)
		if (D < dist(attacked.first, attacked.second, p.first, p.second))
			attacked = { 987654321,987654321 };

	return attacked;
}

// v:궁수 위치, 리턴 : 공격 받은 적 위치 set
set<pair<int, int>> attack(vector<int>v)
{
	set<pair<int, int>>s;

	for (int i = 0; i < v.size(); i++) {
		pair<int, int>p; // 궁수 위치
		p.first = n;
		p.second = v[i];

		pair<int, int>attacked = enemy(p);
		if (attacked.first == 987654321)
			continue;
		else
			s.insert(attacked);
	}
	return s;
}

// 적 이동
void move_enemy(set<pair<int, int>>s)
{
	// 없어진 적 제거
	set<pair<int, int>>::iterator iter;
	for (iter = s.begin(); iter != s.end(); iter++) {
		int y = (*iter).first;
		int x = (*iter).second;
		map[y][x] = 0;
	}

	// 이동
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < m; j++) {
			// 적이 성으로 들어감
			if (i == n - 1) {
				map[i][j] = 0;
			}
			else {
				if (map[i][j] == 1) {
					map[i][j] = 0;
					map[i + 1][j] = 1;
				}
			}
		}
	}
}

// 남은 적 있는 지 확인
bool check_enemy()
{
	bool no_enemy = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 1) {
				no_enemy = false;
				break;
			}
		}
		if (no_enemy == false)
			break;
	}

	return no_enemy;
}

// 찍어보기용
void print_map()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << map[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	// 궁수 위치 설정하기
	vector<int>arr(m);
	for (int i = 0; i < m; i++)
		arr[i] = i;
	int r = 3; // 궁수 3명
	vector<int>comb(r);
	combination(arr, comb, r, 0, 0);

	int result = 0;
	for (int i = 0; i < archer.size(); i++) {
		start();
		int res = 0;
		set<pair<int, int>>removed;

		while (1) {
			removed = attack(archer[i]);
			res += removed.size();

			if (removed.empty()) {
				if (check_enemy())
					break;
			}

			move_enemy(removed);
			removed.clear();

			//print_map();
		}

		result = max(result, res);
	}

	cout << result;
}