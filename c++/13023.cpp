#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 각 숫자 node로 보고
// 시작 노드로부터 dfs depth 4면 정답 
// 5개 연결된 거랑 동일

int n, m;
vector<int> vec[2001];
bool visited[2001];
bool result;

void init()
{
  cin >> n >> m;
  for(int i = 0; i < m; i++) {
    int to, from;
    cin >> to >> from;
    vec[to].push_back(from);
    vec[from].push_back(to);
  }

  memset(visited, false, sizeof(visited));
  result = false;
}

void dfs(int depth, int node)
{
  // depth : 현재 탐색 깊이
  // node : 현재 노드
  if(depth == 4) {
    result = true;
    return;
  }
  
  visited[node] = true;
  for(int i = 0; i < vec[node].size(); i++) {
    if(result == true)
      return;
    int nextNode = vec[node][i];
    if(visited[nextNode])
      continue;
    dfs(depth + 1, nextNode);
  }

  // 되돌리기
  visited[node] = false;
  return;
}

int main()
{
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  init();
  for(int node = 0; node < n; node++) {
    dfs(0, node);
  }

  cout << result;
}