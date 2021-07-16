#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

// 회전 방법
// xi, di, ki
// xi 배수 번 원판을 di 방향으로 ki칸 회전
// di 0 : 시계 방향, 1 : 반시계 방향
// 원판에 수가 남아 있으면 인접하면서 수가 같은 것 모두 찾는다.
// 그러한 수 없으면 평균보다 큰 수는 1 빼고, 작은 수는 1 더한다.

// N : 원판 개수, M : 원판 내부 초기 숫자 개수, T : 회전 횟수
int N, M, T;
int board[51][51];

// 제거된 수 -1로 처리 (제거 안 될 때 평균보다 작으면 +1, 크면 -1이고 기존 원판 모두 1이상이므로 평균이 1보다 작아질 수 없음)
#define NO -1

typedef struct rot{
	int xi, di, ki;
};

rot rotation[51];

// index 시작 1부터
void init()
{
	cin >> N >> M >> T;
	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= M;j++) {
			cin >> board[i][j];
		}
	}

	for (int i = 1;i <= T;i++) {
		int x, d, k;
		cin >> x >> d >> k;
		rotation[i] = { x,d,k };
	}
}

int tmp[51] = { 0 };

void Rotation(rot r) 
{
	int x = r.xi;
	int d = r.di;
	int k = r.ki;

	// 시계 방향 회전
	if (d == 0) {
		for (int i = x;i <= N;i += x) {
			for (int j = 1;j <= M;j++) {
				int idx = (j + k) % M;
				if (idx == 0)
					idx = M;
				tmp[idx] = board[i][j];
			}
			for (int j = 1;j <= M;j++) {
				board[i][j] = tmp[j];
			}
		}
	}

	// 반시계 방향 회전
	else {
		for (int i = x;i <= N;i += x) {
			for (int j = 1;j <= M;j++) {
				int idx = (j - k);
				if (idx == 0) {
					idx = M;
				}
				else if (idx < 0) {
					idx += M;
				}
				tmp[idx] = board[i][j];
			}
			for (int j = 1;j <= M;j++) {
				board[i][j] = tmp[j];
			}
		}
	}
}

int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,1,-1 };
bool visited[51][51];

// bfs로 돌면서 인접한 수 같은 애들 제거
// (start_y, start_x) 위치 수와 같은 값인 애들 찾기
// return은 벡터 : (start_y, start_x) 값과 인접한 애들
vector<pair<int,int>> bfs(int start_y, int start_x)
{
	// start_y, start_x 위치 값 -1이면 bfs 안 돌게 처리

	queue<pair<int, int>>q;
	q.push({ start_y, start_x });
	visited[start_y][start_x] = true;
	
	vector<pair<int, int>>v;
	v.push_back({ start_y, start_x });

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int i = 0;i < 4;i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny < 1 || ny > N)
				continue;

			if (nx == 0) {
				nx = M;
			}
			else if (nx == (M + 1)) {
				nx = 1;
			}

			if (board[ny][nx] == NO)
				continue;

			if (visited[ny][nx])
				continue;

			if (board[ny][nx] == board[y][x]) {
				visited[ny][nx] = true;
				q.push({ ny,nx });
				v.push_back({ ny,nx });
			}
		}
	}

	// 리턴된 벡터 크기 1이면 인접한 거 없는 경우 : 처리해야됨
	return v;
}

bool flag; // 제거된 거 있는지 여부 판단 true면 있는 거
vector<pair<int, int>>remove_num; // 인접한 수들

void removing()
{
	flag = false;

	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= M;j++) {
			visited[i][j] = false;
		}
	}

	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= M;j++) {
			if (board[i][j] == NO)
				continue;
			if (visited[i][j] == true)
				continue;

			remove_num = bfs(i, j);

			if (remove_num.size() > 1) {
				flag = true;
				for (int a = 0;a < remove_num.size();a++) {
					pair<int, int>p = remove_num[a];
					board[p.first][p.second] = NO;
				}
			}

			remove_num.clear();
		}
	}

	return;
}

// flag == false 일 때만 진행
// 평균에서 +- 1
void plus_minus()
{
	int cnt = 0;
	int sum = 0;

	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= M;j++) {
			if (board[i][j] != NO) {
				cnt++;
				sum += board[i][j];
			}
		}
	}

	if (cnt == 0)
		return;

	int r = sum % cnt;
	if (r == 0) {
		int ave = sum / cnt;
		for (int i = 1;i <= N;i++) {
			for (int j = 1;j <= M;j++) {
				if (board[i][j] == NO)
					continue;
				if (board[i][j] > ave) {
					board[i][j]--;
				}
				else if (board[i][j] < ave) {
					board[i][j]++;
				}
			}
		}
	}

	else {
		int ave = sum / cnt; // 나머지 가지고 있음 ave = ave + 0.xxx
		for (int i = 1;i <= N;i++) {
			for (int j = 1;j <= M;j++) {
				if (board[i][j] == NO)
					continue;
				if (board[i][j] > ave) {
					board[i][j]--;
				}
				else {
					// 나머지 가지므로 int로 평균과 같은 경우도 ++
					board[i][j]++;
				}
			}
		}
	}

	return;
}

// 원판에 수 남아있는지 확인
int isCnt()
{
	int cnt = 0;

	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= M;j++) {
			if (board[i][j] != NO) {
				cnt++;
				break;
			}
		}
	}
	return cnt;
}

// 원판에 남은 수 합 
int sum_board()
{
	int sum = 0;
	for (int i = 1;i <= N;i++) {
		for (int j = 1;j <= M;j++) {
			if (board[i][j] != NO)
				sum += board[i][j];
		}
	}
	return sum;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int result = 0;
	bool No_number = false;

	init();

	for (int i = 1;i <= T;i++) {
		rot r = rotation[i];
		Rotation(r);

		if (isCnt() == 0) {
			result = 0;
			No_number = true;
			break;
		}

		else {
			removing();
			if (flag == false) {
				plus_minus();
			}
		}
	}

	if (No_number) {
		cout << result;
	}
	else {
		result = sum_board();
		cout << result;
	}
}

