#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int n, m;
int map[51][51];
vector<pair<int, int>> sharks;
int result;
// 두 점 거리 = max(|x1 - x2|, |y1 - y2|)
// 상어 위치 저장해놓고
// 각 점마다 거리 계산하고 최소값(안전거리)만 저장
// 전체 안전거리 중 최대값 구하기

void init()
{
  cin >> n >> m;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      cin >> map[i][j];
      if(map[i][j] == 1) {
        sharks.push_back({i, j});
        map[i][j] = -1;
      }
    }
  }
  result = 0;
}

int dist(pair<int,int> p1, pair<int,int> p2)
{
  return max(abs(p1.first - p2.first), abs(p1.second - p2.second));
}

void calc()
{
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(map[i][j] == -1)
        continue;
      
      pair<int,int> p = {i, j};
      for(auto shk : sharks) {
        int d = dist(p, shk);
        if(map[i][j] == 0)
          map[i][j] = d;
        else
          map[i][j] = min(map[i][j], d);
      }
    }
  }

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(map[i][j] == -1)
        continue;
      result = max(result, map[i][j]);
    }
  }
}

int main() {
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  init();
  calc();
  cout << result;
}