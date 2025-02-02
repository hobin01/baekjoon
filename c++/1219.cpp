#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// SPFA로 계산하면서 버는 것까지 고려해서 업데이트 여부 결정해야 함 
// 음수 사이클 대신 무한 사이클 여부 고려해야 함 

int n, m;
int start, finish;
long long inf = -987654321;

vector<pair<int, long long>> graph[50];
queue<int> q;
bool inQueue[50];
long long earn[50];
long long dist[50];
int cycleCount[50];

void init() {
    cin >> n >> start >> finish >> m;

    int from, to;
    long long cost;
    for(int i = 0; i < m; i++) {
        cin >> from >> to >> cost;
        graph[from].push_back({to, -1 * cost});
    }

    for(int i = 0; i < n; i++) {
        cin >> earn[i];
        inQueue[i] = false;
        dist[i] = inf;
        cycleCount[i] = 0;
    }

    // 버는 금액과 가는 비용 미리 상쇄해서 계산 
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < graph[i].size(); j++) {
            graph[i][j].second += earn[graph[i][j].first];
        }
    }
}

bool possible(int startNode, int finishNode) {
    // gg case 체크 
    queue<int> que; 
    bool visited[50];
    for(int i = 0; i < n; i++) visited[i] = false;

    que.push(startNode);
    visited[startNode] = true;

    while(!que.empty()) {
        int cur = que.front();
        que.pop();

        for(int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i].first;
            if(visited[next] == false) {
                que.push(next);
                visited[next] = true;
            }
        }
    }

    // 방문할 수 있는 지 여부 체크 
    if(visited[finishNode]) return true;
    return false;
}

int SPFA() {

    q.push(start);
    dist[start] = earn[start];
    inQueue[start] = true;
    cycleCount[start] = 1;

    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        inQueue[cur] = false;

        long long d = dist[cur];

        for(int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i].first;
            long long cost = graph[cur][i].second;

            // 업데이트 되는 경우
            if(dist[next] < (d + cost)) {
                dist[next] = (d + cost);

                // 다음 노드 큐에 없음
                if(inQueue[next] == false) {

                    // 사이클 있는 경우 (무한대 증가 가능)
                    // 사이클 있는데에서 finish까지 가는 경로 있으면 -1 리턴 
                    // 사이클 없으면 큐에 넣기 
                    if((cycleCount[next] + 1) >= n) {
                        // Gee case
                        bool chk = possible(next, finish);
                        if(chk) return -1;
                    } else {
                        q.push(next);
                        inQueue[next] = true;
                        cycleCount[next]++;
                    }
                }
            }
        }
    }

    // 도착 못 함 
    // gg case
    if(dist[finish] == inf) {
        return 0;
    }

    return 1;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();

    bool chk = possible(start, finish);
    if(chk == false) {
        cout << "gg";
        return 0;
    }

    int res = SPFA();
    if(res == -1) cout << "Gee";
    else if(res == 0) cout << "gg";
    else cout << dist[finish];

    return 0;
}
