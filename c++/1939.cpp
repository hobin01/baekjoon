#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int n, m;
int a, b, c;
int src, dest;

// vec[i] : {연결된 노드, 둘 사이 무게}
vector<pair<int, int>> vec[10001];
// scr와 i번 노드까지 계산된 최소 무게
int weight[10001];

void init()
{
  cin >> n >> m;
  for(int i = 0; i < m; i++) {
    cin >> a >> b >> c;
    if(a == b)
      continue;
    vec[a].push_back({b, c});
    vec[b].push_back({a, c});
  }

  cin >> src >> dest;

  // c >= 1
  memset(weight, 0, sizeof(weight));
}

void dijk()
{
  priority_queue<pair<int, int>> pq;

  pq.push({0, src});
  weight[src] = 0;

  while(!pq.empty()) {
    int w = pq.top().first;
    int node = pq.top().second;
    pq.pop();

    if(weight[node] > w)
      continue;

    for(auto v : vec[node]) {
      int nextNode = v.first;
      int nextWeight = v.second;
      int tmpWeight = 0;
      if(w == 0)
        tmpWeight = nextWeight;
      else
        tmpWeight = min(w, nextWeight);
      
      if(weight[nextNode] < tmpWeight) {
        weight[nextNode] = tmpWeight;
        pq.push({tmpWeight, nextNode});
      }
    }
  }

  cout << weight[dest];
}

int main()
{
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  init();
  dijk();
}
