#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 판에 0, 1 브루트포스로 놓고
// 0 으로 놓인 곳은 가로
// 1 로 놓인 곳은 세로
// 라 하고 계산

int n, m;
int map[4][4]; // 숫자판
bool check[4][4]; // 0, 1 놓기
bool visited[4][4];
int result;

void init()
{
  cin >> n >> m;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      char c;
      cin >> c;
      map[i][j] = c - '0';
    }
  }

  result = 0;
}

void getCheck(int num)
{
  memset(check, false, sizeof(check));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      bool tmp = num & 1;
      check[i][j] = tmp;
      num >>= 1;
    }
  }
}

void calc()
{
  int res = 0;
  memset(visited, false, sizeof(visited));

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(visited[i][j])
        continue;

      vector<int> v;
      
      if(check[i][j] == 0) {
        for(int k = j; k < m; k++) {
          if(check[i][k] == 1)
            break;
          v.push_back(map[i][k]);
          visited[i][k] = true;
        }
      }

      else {
        for(int k = i; k < n; k++) {
          if(check[k][j] == 0)
            break;
          v.push_back(map[k][j]);
          visited[k][j] = true;
        }
      }

      int tmp = 0;
      for(auto num : v) {
        tmp = tmp * 10 + num;
      }
      res += tmp;
    }
  }

  result = max(result, res);
}

int main() {
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  init();
  int bitMax = 1 << (n * m + 1);
  for(int bit = 0; bit < bitMax; bit++) {
    getCheck(bit);
    calc();
  }

  cout << result;
}