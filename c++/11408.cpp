#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>

using namespace std;

int n, m;
int source;
int sink;
// source 0, sink n+m+1
// mcmf : edmonds-karp + spfa

struct Edge {
    int from;
    int to;
    int cost;
    int cap;
    int flow;
    int rev; // 해당 엣지의 역방향 기준으로 부모 노드의 몇 번째인지 계산용 (역방향 엣지면 역방향의 역방향 = 정방향 기준)

    Edge(int _from, int _to, int _cost, int _cap, int _flow, int _rev) {
        from = _from;
        to = _to;
        cost = _cost;
        cap = _cap;
        flow = _flow;
        rev = _rev;
    }
};

vector<vector<Edge*>> graph; // n + m + 2; // source : 0, 사람 : 1 ~ n, 일 : n + 1 ~ n + m, sink : n + m + 1
int inf = INT_MAX; // 완전 그래프여도 16억 정도 

void init() {
    cin >> n >> m;
    source = 0;
    sink = n + m + 1;

    graph.resize(n + m + 2);

    // source -> 직원 : cost = 0, cap = 1
    // 일 -> sink : cost = 0, cap = 1 (일 1개당 1명 맡음 : 각 일에서 sink로의 유량은 최대 1 = cap 1)
    // 직원 -> 일 : cost = 월급, cap = 1

    // source -> 직원 
    for(int i = 1; i <= n; i++) {
        Edge* edge = new Edge(0, i, 0, 1, 0, graph[i].size());
        Edge* revEdge = new Edge(i, 0, 0, 0, 0, graph[source].size());
        graph[source].push_back(edge);
        graph[i].push_back(revEdge);
    }

    // 직원 -> 일 
    // total : 할 수 있는 일 개수, num : 일 번호, pay : 해당 일 보수
    int total, num, pay;
    for(int i = 1; i <= n; i++) {
        cin >> total;
        vector<pair<int, int>> works(total);
        for(int j = 0; j < total; j++) {
            cin >> num >> pay;
            works[j].first = num;
            works[j].second = pay;
        }

        for(int j = 0; j < total; j++) {
            num = works[j].first + n;
            pay = works[j].second;

            Edge* edge = new Edge(i, num, pay, 1, 0, graph[num].size());
            Edge* revEdge = new Edge(num, i, -1 * pay, 0, 0, graph[i].size());
            graph[i].push_back(edge);
            graph[num].push_back(revEdge);
        }
    }

    // 일 -> sink 
    for(int i = 1; i <= m; i++) {
        Edge* edge = new Edge(n + i, sink, 0, 1, 0, graph[sink].size());
        Edge* revEdge = new Edge(sink, n + i, 0, 0, 0, graph[n + i].size());
        graph[n + i].push_back(edge);
        graph[sink].push_back(revEdge);
    }
}

pair<int, int> mcmf() {
    int maxFlow = 0;
    int minCost = 0;
    pair<int, int> res = {0, 0};

    while(true) {
        vector<int> parents(n + m + 2, -1); // 증가 경로 상 부모 노드 
        vector<int> parentsEdge(n + m + 2, -1); // 증가 경로 상에서 부모의 몇 번째 엣지인지 
        queue<int> q; // 증가 경로 계산용 
        vector<bool> inQueue(n + m + 2, false);
        vector<int> dist(n + m + 2, inf); // spfa 최단 거리 계산용 

        q.push(source);
        inQueue[source] = true;
        dist[source] = 0;

        while(!q.empty()) {
            // spfa
            // mcmf 계산할 때는 음수 사이클 없음 
            int cur = q.front();
            q.pop();
            inQueue[cur] = false;

            // 현재 체크된 거까지 가는 최단 경로 없음
            if(dist[cur] == inf) continue;

            for(int i = 0; i < graph[cur].size(); i++) {
                Edge *e = graph[cur][i];

                int remainFlow = e->cap - e->flow;
                int next = e->to;
                int cost = e->cost;

                // 유량 갈 수 있고, 비용 최소 인 거 선택 
                if((remainFlow > 0) && (dist[next] > (dist[cur] + cost))) {
                    dist[next] = dist[cur] + cost;
                    parents[next] = cur;
                    parentsEdge[next] = i;

                    if(inQueue[next] == false) {
                        q.push(next);
                        inQueue[next] = true;
                    }
                }
            }
        }
        
        // 증가 경로 더 없음
        if(parents[sink] == -1) break;

        // 잔여 용량만큼 업데이트 (증가 경로 중 가장 작은 거)
        int minFlow = inf;
        int node, parent, parentEdgeIdx;
        for(node = sink; node != source; node = parents[node]) {
            parent = parents[node];
            parentEdgeIdx = parentsEdge[node];
            Edge* e = graph[parent][parentEdgeIdx];
            minFlow = min(minFlow, e->cap - e->flow);
        }

        // 유량 추가 및 cost 추가
        for(node = sink; node != source; node = parents[node]) {
            parent = parents[node];
            parentEdgeIdx = parentsEdge[node];
            Edge* e = graph[parent][parentEdgeIdx];
            Edge* rev = graph[node][e->rev];

            // 유량 추가
            e->flow += minFlow;
            rev->flow -= minFlow;
        }

        maxFlow += minFlow;
        minCost += (dist[sink] * minFlow);
    }

    res = {maxFlow, minCost};
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    init();
    pair<int, int> res = mcmf();
    cout << res.first << '\n' << res.second;
}
