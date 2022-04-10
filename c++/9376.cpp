#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>

using namespace std;

int t, h, w;
char map[102][102]; // 감옥 바깥을 '.'으로 만들기, 상하좌우 2씩 늘어남
pair<int, int>crime[3]; // 범인의 위치 
bool visited[3][102][102]; // 방문 여부

// 상근, 범인1,2 의 해당 위치까지 갈 때
// 열고 온 문의 최소 개수
int door_count[3][102][102];
int inf = 987654321; // door_count의 inf값 (문은 최대 1만개 열림)

// 이동
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };

// 상근이는 (0,0)에 있는 죄수라 생각
// 죄수가 해당 위치까지 열고 온 문의 최소 개수를 3명에 대해 다 더함
// 그 값이 최솟값인 것을 구한다. 
// 해당 위치가 문인 경우 -2 (3명 다 열었으므로)

// 우선순위 큐 이용해서 bfs 돌리기 
// (그냥 큐로 해도 상관없음, 최솟값 구하는 거라 우선순위 큐가 시간은 더 빠름)
// 문을 최소 개수로 열어야 하므로 {문 개수, {y,x}} 일 때 
// 문 개수가 오름차순되도록 우선순위 큐 설정 (top이 가장 작은 값)
// 죄수마다 해당 위치 방문 했거나 벽이면 pass
// 그렇지 않다면 기존 문의 값보다 작으면 해당 값으로 업데이트, 큐에 넣기

// h,w 입력, 초기화
void init()
{
	cin >> h >> w;

	for (int i = 0; i <= h + 1; i++) {
		for (int j = 0; j <= w + 1; j++) {
			map[i][j] = '.';
			door_count[0][i][j] = inf;
			door_count[1][i][j] = inf;
			door_count[2][i][j] = inf;
			visited[0][i][j] = false;
			visited[1][i][j] = false;
			visited[2][i][j] = false;
		}
	}

	crime[0] = { -1,-1 };
	crime[1] = { -1,-1 };
	crime[3] = { 0,0 };
}

// 감옥 만들기
void make_map()
{
	// 감옥 바깥 '.'으로 채우기
	for (int i = 0; i <= h + 1; i++) {
		map[i][0] = '.';
		map[i][w + 1] = '.';
	}
	for (int i = 0; i <= w + 1; i++) {
		map[0][i] = '.';
		map[h + 1][i] = '.';
	}
	
	// 감옥 만들기
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			cin >> map[i][j];
			if (map[i][j] == '$') {
				if (crime[0].first == -1)
					crime[0] = { i,j };
				else
					crime[1] = { i,j };
			}
		}
	}
}

// idx번째 범인의 door_count 계산 (bfs)
void calculate_door(int idx)
{
	// 우선순위 큐 : {문 개수, {y, x}}, 문 개수에 대해 오름차순 (top:가장 작음)
	priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > >pq;
	// 그냥 큐, 성능은 우선순위 큐가 더 좋지만 그냥 큐로 해도 됨.
	// queue<pair<int, pair<int, int>>>pq;

	int now_y = crime[idx].first;
	int now_x = crime[idx].second;

	pq.push({ 0,{now_y,now_x} });
	visited[idx][now_y][now_x] = true;
	door_count[idx][now_y][now_x] = 0;

	while (!pq.empty())
	{
		int cnt = pq.top().first;
		int y = pq.top().second.first;
		int x = pq.top().second.second;

		//int cnt = pq.front().first;
		//int y = pq.front().second.first;
		//int x = pq.front().second.second;

		pq.pop();

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			// 맵 안에 있을 때
			if (ny >= 0 && ny <= (h + 1) && nx >= 0 && nx <= (w + 1)) {
				
				// 벽인 경우
				if (map[ny][nx] == '*')
					continue;

				// 이미 방문한 경우도 더 나은 경로 존재

				// 가능한 경우
				int next_cnt = cnt;
				// 다음 칸이 문인 경우 기존 값+1
				if (map[ny][nx] == '#')
					next_cnt++;

				// 다음 칸의 문 개수보다 더 나은 경우면
				// 나은 경우로 업데이트, 큐에 넣기
				if (door_count[idx][ny][nx] > next_cnt) {
					door_count[idx][ny][nx] = next_cnt;
					visited[idx][ny][nx] = true;
					pq.push({ next_cnt,{ny,nx} });
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> t;
	while (t--)
	{
		init();
		make_map();

		for (int idx = 0; idx < 3; idx++)
			calculate_door(idx);

		// 최솟값 구하기
		// 모든 위치에서 죄수들의 문 개수를 다 더함
		// 그 중 최소인 것이 답 (모두 해당 위치로 갈 수 있으므로 만난 경우)
		// 해당 위치가 문인 경우 -2 (3명 모두 문을 연것이므로)
		int result = inf;

		for (int i = 0; i <= h + 1; i++) {
			for (int j = 0; j <= w + 1; j++) {
				// 벽이면 계산 안해도 됨
				if (map[i][j] == '*')
					continue;

				// 해당 위치에 한 명이라도 안 오면 안 됨
				if (visited[0][i][j] == false || visited[1][i][j] == false || visited[2][i][j] == false)
					continue;

				int sum = 0;
				for (int k = 0; k < 3; k++)
					sum += door_count[k][i][j];

				// 문에서 만난 경우
				if (map[i][j] == '#')
					sum -= 2;

				result = min(result, sum);
			}
		}

		cout << result << '\n';
	}
}