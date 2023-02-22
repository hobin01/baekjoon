#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

// 사이클 만드는 노드들을 루트로 잡고
// 자식 노드들까지 거리 구하면 됨
// n개 입력이 주어지므로
// 노드와 엣지 개수 동일 : 사이클은 1개만 존재 (0개도 X)

int n;
vector<int> tree[3001];
bool visited[3001];
int parent[3001]; // 부모 노드 확인용
vector<int> cycle;
bool check; // 사이클 확인용
int result[3001];

void init()
{
  cin >> n;
  int to, from;
  for(int i = 0; i < n; i++) {
    cin >> to >> from;
    tree[to].push_back(from);
    tree[from].push_back(to);
    visited[i + 1] = false;
    result[i + 1] = 0;
  }
  check = false;
}

void getCycle(int node)
{
  // 사이클 찾기
  // 부모 아닌 방문했던 노드 도달하면 거기가 사이클
  if(check)
    return;
  visited[node] = true;
  
  for(auto next_node : tree[node]) {
    if(check)
      return;
    if(visited[next_node] && parent[node] != next_node) {
      // 부모 아닌 방문했던 노드 방문 : 사이클 생성
      check = true;
      
      int start = node;
      int last = next_node;
      while(last != start) {
        cycle.push_back(start);
        start = parent[start];
      }
      cycle.push_back(last);

      return;
    }

    else if(visited[next_node] == false) {
      // 계속 탐색
      parent[next_node] = node;
      getCycle(next_node);
    }
  }
}

void getResult()
{
  // 사이클 안에 있는 애들은 답 0
  for(auto c : cycle) {
    result[c] = 0;
  }
  memset(visited, false, sizeof(visited));

  // 나머지 애들은 직접 구해야 함
  queue<pair<int, int>> q; // {위치, 거리}
  for(auto c : cycle) {
    q.push({c, 0});
    visited[c] = true;
  }

  while(!q.empty()) {
    int node = q.front().first;
    int dist = q.front().second;
    q.pop();

    for(auto v : tree[node]) {
      if(visited[v])
        continue;
      result[v] = dist + 1;
      visited[v] = true;
      q.push({v, dist + 1});
    }
  }

  for(int i = 1; i <= n; i++)
    cout << result[i] << ' ';
}

int main() {
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  init();
  getCycle(1);
  getResult();
}