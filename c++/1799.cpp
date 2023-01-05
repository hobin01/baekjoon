#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int n;
int map[11][11];
bool check[11][11]; // 놓을 수 있는 지 여부
int start_y[2] = {-1, -1};
int start_x[2] = {-1, -1};
int result[2];

vector<pair<int,int>> vec0;
vector<pair<int,int>> vec1;

// 뒤에 남은 가능한 칸을 합친 것보다 현재 결과가 더 크면 탐색 안 해도 됨
// 까만칸 (0,0 색), 흰색 (0,1 색) 분리해서 계산 

void init()
{
  cin >> n;
  memset(check, false, sizeof(check));
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cin >> map[i][j];
      if(map[i][j] == 1) {
        check[i][j] = true; // 놓을 수 있음
        if((i + j) % 2 == 0)
          vec0.push_back({i, j});
        else
          vec1.push_back({i, j});
      }
    }
  }

  int chk1 = false;
  int chk2 = false;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {

      if(chk1 == false)
        if(check[i][j] == true && (i + j) % 2 == 0) {
          start_y[0] = i;
          start_x[0] = j;
          chk1 = true;
        }

      if(chk2 == false)
        if(check[i][j] == true && (i + j) % 2 == 1) {
          start_y[1] = i;
          start_x[1] = j;
          chk2 = true;
        }
    }
  }

  result[0] = 0; // 체스판 기준 까만칸
  result[1] = 0; // 체스판 기준 흰칸
}

vector<pair<int,int>> remain(int y, int x, int color)
{
  // 뒤에 남은 가능한 칸 개수
  // y, x : 현재 놓을 위치
  vector<pair<int, int>> v;
  
  for(int i = y; i < n; i++) {
    for(int j = 0; j < n; j++) {
      // 이전 칸
      if(i == y && j < x)
        continue;

      if(check[i][j] == true && (i + j) % 2 == color)
        v.push_back({i, j});
    }
  }

  return v;
}

vector<pair<int,int>> noFrom(int y, int x)
{
  // y, x 위치에 놓음으로써 만드는 불가능한 영역

  vector<pair<int, int>> v;

  v.push_back({y, x});
  check[y][x] = false;
  
  // 대각선 오른 위
  int ny = y - 1;
  int nx = x + 1;
  
  while(ny >= 0 && nx < n) {
    if(check[ny][nx] == true) {
      v.push_back({ny, nx});
      check[ny][nx] = false;
    }
    ny--;
    nx++;
  }

  // 대각선 오른 아래
  ny = y + 1;
  nx = x + 1;
  
  while(ny < n && nx < n) {
    if(check[ny][nx] == true) {
      v.push_back({ny, nx});
      check[ny][nx] = false;
    }

    ny++;
    nx++;
  }

  // 대각선 왼 위
  ny = y - 1;
  nx = x - 1;
  while(ny >= 0 && nx >= 0) {
    if(check[ny][nx] == true) {
      v.push_back({ny, nx});
      check[ny][nx] = false;
    }

    ny--;
    nx--;
  }

  // 대각선 왼 아래
  ny = y + 1;
  nx = x - 1;
  while(ny < n && nx >= 0) {
    if(check[ny][nx] == true) {
      v.push_back({ny, nx});
      check[ny][nx] = false;
    }

    ny++;
    nx--;
  }

  return v;
}

vector<pair<int,int>> dfs(int y, int x, int res, int color)
{
  // 탐색
  vector<pair<int,int>> v_no = noFrom(y, x);
  vector<pair<int,int>> v_rem = remain(y, x, color);

  // 뒤에 더 해도 안 됨
  if(result[color] >= res + v_rem.size() + 1)
    return v_no;

  // 마지막 놓을 수 있었던 경우
  if(v_rem.size() == 0) {
    result[color] = max(result[color], res + 1);
    return v_no;
  }

  // 다음 칸부터 놓을 수 있는 칸들에 놓아보기
  for(auto v : v_rem) {
    // 못 놓는 칸
    if(check[v.first][v.second] == false)
      continue;
    
    vector<pair<int,int>> v_no_ret = dfs(v.first, v.second, res + 1, color);

    // 못 놓게 만든 칸 되돌리기
    for(auto v2 : v_no_ret) {
      check[v2.first][v2.second] = true;
    }
  }

  return v_no;
}

int main()
{
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  init();
  vector<pair<int,int>> tmp;
  // 까만칸에 놓을 수 있는 경우
  if(start_y[0] != -1) {
    for(auto v : vec0) {
      tmp = dfs(v.first, v.second, 0, 0);
      for(auto t : tmp) {
        check[t.first][t.second] = true;
      }
    }
  }
  // 흰 칸에 놓을 수 있는 경우
  if(start_y[1] != -1) {
    for(auto v : vec1) {
      tmp = dfs(v.first, v.second, 0, 1);
      for(auto t : tmp) {
        check[t.first][t.second] = true;
      }
    }
  }
  cout << result[0] + result[1];
}