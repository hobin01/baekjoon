#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

int N, M;
int map[51][51]; // 입력으로 주어지는 방 정보
bool visited[51][51]; // 방문 여부 체크
int room[51][51]; // 방 번호 주어졌을 때

int dy[4] = {0, -1, 0, 1};
int dx[4] = {-1, 0, 1, 0}; // 서북동남 (1,2,4,8)

int num = 0; // 방 번호 및 개수

void init()
{
  cin >> N >> M;
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < N; j++) {
      cin >> map[i][j];
    }
  }
  memset(visited, false, sizeof(visited));
}

void bfs(int sy, int sx)
{
  // num : 방 번호
  // sy, sx : 시작위치 y, x
  queue<pair<int, int>> q;

  if(visited[sy][sx]) {
    return;
  }

  num++; // 방 번호 올리고 시작
  
  q.push({sy, sx});
  visited[sy][sx] = true;
  room[sy][sx] = num;

  while(!q.empty()) {
    int y = q.front().first;
    int x = q.front().second;
    q.pop();

    int m = map[y][x];
    int possible = 15 - m;

    int idx = 0;
    while(possible != 0) {
      if(possible & 1) {
        int ny = y + dy[idx];
        int nx = x + dx[idx];

        if(ny < 0 || nx < 0 || ny >= M || nx >= N) {
          idx++;
          possible >>= 1;
          continue;
        }
        if(visited[ny][nx]) {
          idx++;
          possible >>= 1;
          continue;
        }

        q.push({ny, nx});
        visited[ny][nx] = true;
        room[ny][nx] = num;

        idx++;
        possible >>= 1;
      } 
      else {
        idx++;
        possible >>= 1;
      }
    }
  }
}

void calc()
{
  // 방 계산
  for(int y = 0; y < M; y++) {
    for(int x = 0; x < N; x++) {
      bfs(y, x);
    }
  }

  cout << num << '\n'; // 방 개수

  // 방 별 칸 계산
  vector<int> v_cnt(num + 1, 0);
  for(int y = 0; y < M; y++) {
    for(int x = 0; x < N; x++) {
      int roomNum = room[y][x];
      v_cnt[roomNum]++;
    }
  }

  vector<int> tmp = v_cnt;
  sort(tmp.rbegin(), tmp.rend());

  cout << tmp[0] << '\n'; // 방 최대 넓이

  // 벽 한 개 없을 때 가장 큰 방
  // == 번호 다른데 마주보는 경우
  // 그 방 넓이 합이 가장 큰 경우
  int biggest = 0;

  for(int y = 0; y < M; y++) {
    for(int x = 0; x < N; x++) {
      int cur = room[y][x];
      int cur_area = v_cnt[cur];

      for(int idx = 0; idx < 4; idx++) {
        int ny = y + dy[idx];
        int nx = x + dx[idx];

        if(ny < 0 || nx < 0 || ny >= M || nx >= N)
          continue;

        int next = room[ny][nx];
        int next_area = v_cnt[next];
        if(cur == next)
          continue;

        biggest = max(biggest, cur_area + next_area);
      }
    }
  }

  cout << biggest;
}

int main()
{
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  init();
  calc();
}