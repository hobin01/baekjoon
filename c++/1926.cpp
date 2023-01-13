#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int map[501][501];
vector<int> img;
bool visited[501][501];
int dy[4] = {0, 0, 1, -1};
int dx[4] = {1, -1, 0, 0};

void init()
{
  cin >> n >> m;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      cin >> map[i][j];
      visited[i][j] = false;
    }
  }
}

void bfs(int sy, int sx)
{
  // sy, sx : 시작 위치
  // res : 만든 그림 크기
  // img 벡터에 넣기
  
  int res = 0;
  
  queue<pair<int,int>> q;
  q.push({sy, sx});
  visited[sy][sx] = true;
  res++;

  while(!q.empty()) {
    pair<int, int> loc = q.front();
    q.pop();
    int y = loc.first;
    int x = loc.second;
    
    for(int i = 0; i < 4; i++) {
      int ny = y + dy[i];
      int nx = x + dx[i];

      if(ny < 0 || ny >= n || nx < 0 || nx >= m)
        continue;
      if(visited[ny][nx])
        continue;

      if(map[ny][nx] == 1) {
        visited[ny][nx] = true;
        q.push({ny, nx});
        res++;
      }
    }
  }

  img.push_back(res);
}

int main() {
  init();

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(visited[i][j] || map[i][j] == 0)
        continue;
      bfs(i, j);
    }
  }

  sort(img.begin(), img.end());

  cout << img.size() << '\n';
  if(img.size() == 0)
    cout << 0;
  else
    cout << img[img.size() - 1];
}