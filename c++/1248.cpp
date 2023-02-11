#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

// 백트래킹으로 입력 스트링 조건 만족할 때까지 탐색

int n;
char map[11][11];
vector<int> result;
bool ok; // 답 찾았는지 확인용

void init()
{
  cin >> n;
  int idx = 0;
  for(int i = 0; i < n; i++) {
    for(int j = i; j < n; j++) {
      cin >> map[i][j];
    }
  }
  ok = false;
  result.resize(n);
}

bool check(int idx)
{
  int sum = 0;
  for(int i = idx; i >= 0; i--) {
    sum += result[i];
    if(map[i][idx] == '+' && sum <= 0)
      return false;
    if(map[i][idx] == '-' && sum >= 0)
      return false;
    if(map[i][idx] == '0' && sum != 0)
      return false;
  }
  return true;
}

void dfs(int idx)
{
  // idx : 현재 조건 맞는지 확인할 위치

  // 답 찾았음
  if(ok)
    return;

  // 다 찾음
  if(idx == n) {
    for(auto v : result) {
      cout << v << ' ';
    }
    ok = true;
    return;
  }

  for(int i = -10; i <= 10; i++) {
    result[idx] = i;
    // 조건 만족하는 지 확인
    int sum = 0;
    bool chk = check(idx);
    if(chk)
      dfs(idx + 1);
  }

  return;
}

int main()
{
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  init();
  dfs(0);
}
