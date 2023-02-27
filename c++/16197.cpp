#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// o : 동전, . : 빈 칸, # : 벽
int n, m;
char map[21][21];
pair<int, int> coin1;
pair<int, int> coin2;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
int res = 987654321;

void init()
{
  cin >> n >> m;
  coin1 = {-1, -1};
  coin2 = {-1, -1};
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      cin >> map[i][j];
      if(map[i][j] == 'o' && coin1.first == -1)
        coin1 = {i, j};
      else if(map[i][j] == 'o' && coin1.first != -1)
        coin2 = {i, j};
    }
  }
}

bool check(pair<int, int> c)
{
  int y = c.first;
  int x = c.second;

  // 떨어짐
  if(y < 0 || y >= n || x < 0 || x >= m)
    return true;

  // 아닌 경우
  return false;
}

void calc(pair<int, int> c1, pair<int, int> c2, int cnt) 
{
  // 더 안 해도 됨
  if(cnt > 10)
    return;
  bool check1 = check(c1);
  bool check2 = check(c2);
  // 둘 다 떨어짐
  if(check1 == true && check2 == true)
    return;
  // 둘 중 하나 떨어짐
  else if(check1 == true && check2 == false) {
    res = min(res, cnt);
    return;
  }
  else if(check1 == false && check2 == true) {
    res = min(res, cnt);
    return;
  }
  // 둘 다 남아있음
  else {
    for(int i = 0; i < 4; i++) {
      int ny1 = c1.first + dy[i];
      int nx1 = c1.second + dx[i];
      int ny2 = c2.first + dy[i];
      int nx2 = c2.second + dx[i];

      if(map[ny1][nx1] == '#') {
        ny1 = c1.first;
        nx1 = c1.second;
      }
      if(map[ny2][nx2] == '#') {
        ny2 = c2.first;
        nx2 = c2.second;
      }

      calc({ny1, nx1}, {ny2, nx2}, cnt + 1);
    }
  }
  return;
}

int main()
{
  init();
  calc(coin1, coin2, 0);
  if(res == 987654321)
    cout << -1;
  else
    cout << res;
}