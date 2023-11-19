#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

int n, m;
vector<pair<int, int>> vec[1001]; // {연결된 노드, 가중치}
int dist[1001]; // 거리 최대 1000만

void init()
{
    cin >> n >> m;
    int f, t, w; // from, to, weight
    for(int i = 0; i < (n-1); i++) {
        cin >> f >> t >> w;
        vec[f].push_back({t, w});
        vec[t].push_back({f, w});
    }
}

void dist_clear()
{
    for(int i = 0; i < 1001; i++) {
        dist[i] = 987654321;
    }
}

void dijkstra(int start, int last)
{
    // 우선순위 큐 이용한 다익스트라
    dist[start] = 0;
    
    // {현재까지 거리, 현재 탐색 노드}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq; 
    pq.push({0, start});
    
    while(!pq.empty()) {
        int d = pq.top().first;
        int cur = pq.top().second;
        pq.pop();
        
        // 계산했던 값이 더 작은 경우 (더 안 해도 됨)
        if(dist[cur] < d)
            continue;
            
        // 탐색 
        for(auto v : vec[cur]){
            int next = v.first;
            int nd = v.second + d;
            
            // 갱신
            if(dist[next] > nd) {
                dist[next] = nd;
                pq.push({nd, next});
            }
        }
    }
    
    cout << dist[last] << '\n';
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    
    int start, last;
    for(int i = 0; i < m; i++) {
        dist_clear();
        cin >> start >> last;
        dijkstra(start, last);
    }
}