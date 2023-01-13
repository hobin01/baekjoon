#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, s, w;
int S[9];
int W[9];
// 부딪히면 내구도 - 상대 무게 됨
// 내구도 0 이하면 깨진 것
// 0, 1, 2, ... 순으로 들 수 있음. 끝까지 가면 끝

int result;

void init()
{
  cin >> n;
  for(int i = 0; i < n; i++) {
    cin >> s >> w;
    S[i] = s;
    W[i] = w;
  }
  result = 0;
}

void dfs(int idx)
{ 
  if(idx == n) {
    int res = 0;
    for(int i = 0; i < n; i++) {
      if(S[i] <= 0)
        res++;
    } 
    result = max(result, res);
    return;
  }

  if(S[idx] <= 0) {
    dfs(idx + 1);
    return;
  }

  for(int i = 0; i < n; i++) {
    if(i == idx)
      continue;

    int s1 = S[idx];
    int s2 = S[i];

    if(s1 <= 0 || s2 <= 0) {
      dfs(idx + 1);
      continue;
    }
    
    int ns1 = S[idx] - W[i];
    int ns2 = S[i] - W[idx];

    S[idx] = ns1;
    S[i] = ns2;
    
    dfs(idx + 1);

    S[idx] = s1;
    S[i] = s2;
  }

  return;
}

int main() {
  init();
  dfs(0);
  cout << result;
}