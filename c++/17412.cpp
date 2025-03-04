#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, P;
// source 1, sink 2

struct Edge {
    int to;
    int rev; // 역방향 기준 몇 번째 엣지인지 
    int cap;
    int flow;
};

vector<Edge> graph[401];
vector<int> level; // level graph에서 몇 번 level인지 (using bfs)
vector<int> iter; // blocking flow에서 몇 번째까지 탐색했는지 (using dfs)

const int SOURCE = 1;
const int SINK = 2;

const int INF = 987654321; // 문제 상에서 edge 최대 10,000개, cap 모두 1 

void init() {
    cin >> N >> P;

    level.resize(N + 1);
    iter.resize(N + 1);
    
    int from, to;
    for(int i = 0; i < P; i++) {
        cin >> from >> to;
        Edge e = {to, (int)graph[to].size(), 1, 0};
        Edge revE = {from, (int)graph[from].size(), 0, 0};
        graph[from].push_back(e); // 정방향 그래프 추가 
        graph[to].push_back(revE); // 역방향 그래프 추가 
    }
}

void make_level_graph(int source, int sink) {
    // 레벨 그래프 : source -> 노드까지 최단 거리 (cap 남아 있는 경우)
    queue<int> q;
    level[source] = 0;
    q.push(source);

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        // sink까지 최단 거리 계산 완료 (bfs)
        if(node == sink) break;

        // cap 남아 있고, 레벨 안 정해진 경우만 고려 
        for(auto e : graph[node]) {
            if((e.cap - e.flow) > 0 && level[e.to] == -1) {
                level[e.to] = level[node] + 1;
                q.push(e.to);
            }
        }
    }
}

int calc_blocking_flow(int node, int sink, int flow) {
    if(node == sink) return flow;

    // 현재 탐색 노드를 기준으로 blocking 안 될 때까지 dfs
    // block 안 되면 유량은 flow 중 최소값
    while(iter[node] < (int)graph[node].size()) {
        int idx = iter[node];
        Edge e = graph[node][idx];
        if((e.cap - e.flow) > 0 && level[node] < level[e.to]) {
            // cap 남아 있고, 레벨이 더 높은 곳으로 가는 경우 (레벨이 sink보다 더 뒤에 있어서 안 정해질 수도 있음)
            // 현재까지 계산된 flow와 지나갈 edge의 cap 중 최소값이 증강 경로 상 유량 
            int f = calc_blocking_flow(e.to, sink, min(flow, e.cap - e.flow));

            if(f > 0) {
                graph[node][idx].flow += f;
                graph[e.to][e.rev].flow -= f;
                return f;
            }
        }
        iter[node]++;
    }

    return 0;
}

int dinic(int source, int sink) {
    // 최대 유량 계산 
    int flow = 0;

    while(true) {
        // 레벨 그래프 초기화 
        fill(level.begin(), level.end(), -1);
        // 레벨 그래프 계산 
        make_level_graph(source, sink);
        // sink의 level 이 -1인 경우, sink까지 가는 경로 없음. 즉, 더 이상 유량 가는 경로 없음 
        if(level[sink] == -1) break;

        // iter 초기화 
        fill(iter.begin(), iter.end(), 0);
        // blocking flow 계산
        while(true) {
            int f = calc_blocking_flow(source, sink, INF);
            // 최대 유량에 추가 
            flow += f;
            // 현재 레벨 그래프에서는 더 이상 추가할 유량 없음 
            if(f == 0) break;
        } 
    }

    return flow; 
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    cout << dinic(SOURCE, SINK);
}
