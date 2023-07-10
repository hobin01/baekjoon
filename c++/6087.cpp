#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>

using namespace std;
// 꺾이는 최소 개수만 찾으면 됨 
// . : 빈 칸, * : 벽, C : 레이저

int w, h;
char map[101][101];
bool visited[101][101];
int corner[101][101][4];
int dy[4] = {-1, 1, 0, 0}; 
int dx[4] = {0, 0, -1, 1};
// 상하좌우 : 0123
pair<int, int> src = {-1, -1};
pair<int, int> dst = {-1, -1};

void init()
{
  cin >> w >> h;
  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      cin >> map[i][j];
      visited[i][j] = false;
      corner[i][j][0] = 987654321;
      corner[i][j][1] = 987654321;
      corner[i][j][2] = 987654321;
      corner[i][j][3] = 987654321;
      
      if(map[i][j] == 'C') {
        if(src.first == -1) {
          src = {i, j};
        }
        else if(dst.first == -1) {
          dst = {i, j};
        }
      }
    }
  }
}

int changeDir(int dir1, int dir2)
{
  // 0 : 방향 그대로
  // -1 : 상하, 좌우 : 불가능
  // 1 : 꺾이는 경우
  if(dir1 == dir2)
    return 0;

  // 상하, 좌우
  if((dir1 + dir2) % 4 == 1)
    return -1;

  // 꺾이는 경우
  return 1;
}

void bfs()
{
  queue<pair<pair<int, int>, pair<int, int>>> q;
  // {{꺾인 횟수, 방향}, {현재 위치}}

  int sy = src.first;
  int sx = src.second;
  visited[sy][sx] = true;
  corner[sy][sx][0] = 0;
  corner[sy][sx][1] = 0;
  corner[sy][sx][2] = 0;
  corner[sy][sx][3] = 0;
  
  // 시작점 상하좌우 지점
  for(int i = 0; i < 4; i++) {
    int ny = sy + dy[i];
    int nx = sx + dx[i];

    // 벗어남
    if(ny < 0 || nx < 0 || ny >= h || nx >= w)
      continue;
    // 벽
    if(map[ny][nx] == '*')
      continue;
    // 도착
    if(map[ny][nx] == 'C') {
      cout << 0;
      return;
    }

    q.push({{0, i}, {ny, nx}});
    visited[ny][nx] = true;
    corner[ny][nx][i] = 0;
  }

  while(!q.empty()) {
    int cnt = q.front().first.first;
    int dir = q.front().first.second;
    int y = q.front().second.first;
    int x = q.front().second.second;

    q.pop();

    // 도착
    if(y == dst.first && x == dst.second) {
      corner[y][x][dir] = min(corner[y][x][dir], cnt);
      continue;
    }

    for(int i = 0; i < 4; i++) {
      int ny = y + dy[i];
      int nx = x + dx[i];
      int ncnt = cnt;

      // 꺾임
      int change = changeDir(i, dir);
      // 불가능한 경우
      if(change == -1)
        continue;
      ncnt += change;

      // 벗어남
      if(ny < 0 || nx < 0 || ny >= h || nx >= w)
        continue;
      
      // 벽
      if(map[ny][nx] == '*')
        continue;
      
      // 한 번도 안 온 곳
      if(visited[ny][nx] == false) {
        q.push({{ncnt, i}, {ny, nx}});
        visited[ny][nx] = true;
        corner[ny][nx][i] = ncnt;
      }

      // 갔던 곳
      else {
        // 더 좋은 경로
        if(ncnt < corner[ny][nx][i]) {
          q.push({{ncnt, i}, {ny, nx}});
          corner[ny][nx][i] = ncnt;
        }
        // 카운트는 같지만 방향 다른 경우
        else if(ncnt == corner[ny][nx][i] && i != dir) {
          q.push({{ncnt, i}, {ny, nx}});
        }
      }
    }
  }

  int res = 987654321;
  for(int i = 0; i < 4; i++) {
    res = min(res, corner[dst.first][dst.second][i]);
  }
  cout << res;
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