#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

int n, m;
int h, w, sr, sc, fr, fc;
int map[1001][1001];
bool visited[1001][1001];
int dy[4] = {0, 0, 1, -1};
int dx[4] = {1, -1, 0, 0};

void init()
{
  cin >> n >> m;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      cin >> map[i][j];  
    }
  }
  cin >> h >> w >> sr >> sc >> fr >> fc;
  memset(visited, false, sizeof(visited));
}

bool possible(int y, int x, int dir)
{
  // 벗어남
  if(y <= 0 || y > n || x <= 0 || x > m)
    return false;
  if((y + h - 1 > n) || (x + w - 1 > m))
    return false;

  // 벽 있음
  // 옮겨진 곳만 체크
  if(dir == 0) {
    // 우측 이동
    for(int i = 0; i < h; i++) {
      if(map[y + i][x + w - 1] == 1)
        return false;
    }
  }

  else if(dir == 1) {
    // 좌측 이동
    for(int i = 0; i < h; i++) {
      if(map[y + i][x] == 1)
        return false;
    }
  }

  else if(dir == 2) {
    // 아래측 이동
    for(int i = 0; i < w; i++) {
      if(map[y + h - 1][x + i] == 1)
        return false;
    }
  }

  else if(dir == 3) {
    // 위측 이동
    for(int i = 0; i < w; i++) {
      if(map[y][x + i] == 1)
        return false;
    }
  }

  // 벽 없음
  return true;
}

void bfs()
{
  // 왼쪽 위 점, 횟수
  queue<pair<pair<int, int>, int>> q;
  q.push({{sr, sc}, 0});
  visited[sr][sc] = true;

  while(!q.empty()) {
    int y = q.front().first.first;
    int x = q.front().first.second;
    int cnt = q.front().second;

    q.pop();

    // 도착
    if(y == fr && x == fc) {
      cout << cnt;
      return;
    }

    for(int i = 0; i < 4; i++) {
      int ny = y + dy[i];
      int nx = x + dx[i];

      if(possible(ny, nx, i) == false)
        continue;

      if(visited[ny][nx] == true)
        continue;

      q.push({{ny, nx}, cnt + 1});
      visited[ny][nx] = true;
    }
  }

  cout << -1;
  return;
}

int main()
{
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  init();
  bfs();
}