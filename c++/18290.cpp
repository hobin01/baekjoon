#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, k;
int map[11][11];
int result;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
bool visited[11][11];

void init()
{
  cin >> n >> m >> k;
  for(int i = 0; i < n; i ++) {
    for(int j = 0; j < m; j++) {
      cin >> map[i][j];
      visited[i][j] = false;
    }
  }

  result = -987654321; // 최소 -1000000
}

void calc(int y, int x, int cnt, int sum, vector<pair<int, int>> &vec)
{ 
  // y, x : 현재 탐색 위치
  // cnt : 카운트된 개수
  // vec : 인접한 점들
  if(cnt == k) {
    result = max(result, sum);
    return;
  }

  for(int i = y; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(i == y && j < x)
        continue;
      
      if(visited[i][j])
        continue;

      // 인접한 점 목록에 있는 지 확인
      bool chk = false;
      for(auto v : vec) {
        if(v.first == i && v.second == j) {
          chk = true;
          break;
        }
      }

      if(chk)
        continue;

      // 인접한 점 구하기
      int next = 0;
      for(int t = 0; t < 4; t++) {
        int ny = i + dy[t];
        int nx = j + dx[t];
        if(ny < 0 || ny >= n || nx < 0 || nx >= m)
          continue;
        next++;
        vec.push_back({ny, nx});
      }
      
      visited[i][j] = true;
      calc(i, j, cnt + 1, sum + map[i][j], vec);
      // 점, 인접한 점 제거
      visited[i][j] = false;
      for(int t = 0; t < next; t++) {
        vec.erase(vec.begin() + vec.size() - 1);
      }
    }
  }

  return;
}

int main() {
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  init();
  vector<pair<int, int>> vec;
  calc(0, 0, 0, 0, vec);

  cout << result;
}