#include <iostream>

using namespace std;

// no stl mcmf

int n, m;
const int INF = (1 << 31) - 1;
const int MAX_NODE = 802; // 0 : source, 801 : sink, 1 ~ 400 : 직원, 401 ~ 800 : 일
const int WORK_IDX = 400;
const int SOURCE = 0;
const int SINK = 801;

bool graph[MAX_NODE][MAX_NODE]; // 연결 여부만 체크 
int cap[MAX_NODE][MAX_NODE];
int flow[MAX_NODE][MAX_NODE];
int cost[MAX_NODE][MAX_NODE];

void init() {

    for(int i = 0; i < MAX_NODE; i++) {
        for(int j = 0; j < MAX_NODE; j++) {
            graph[i][j] = false; cap[i][j] = 0; flow[i][j] = 0; cost[i][j] = 0;
        }
    }

    cin >> n >> m;

    // source -> 사람 연결 : cap 1, cost 0
    for(int i = 1; i <= n; i++) {
        // 정방향
        graph[SOURCE][i] = true; cap[SOURCE][i] = 1; flow[SOURCE][i] = 0; cost[SOURCE][i] = 0;
        // 역방향 
        graph[i][SOURCE] = true; cap[i][SOURCE] = 0; flow[i][SOURCE] = 0; cost[i][SOURCE] = 0;
    }

    // 사람 -> 일 연결 : cap 1, cost 입력값 
    int total, num, pay;
    for(int i = 1; i <= n; i++) {
        cin >> total;
        while(total--) {
            cin >> num >> pay;
            num = WORK_IDX + num;
            pay = -1 * pay; // 최대 비용이므로 음수 변환 후 최소 비용 계산

            // 정방향 
            graph[i][num] = true; cap[i][num] = 1; flow[i][num] = 0; cost[i][num] = pay;
            // 역방향
            graph[num][i] = true; cap[num][i] = 0; flow[num][i] = 0; cost[num][i] = -1 * pay;
        }
    }

    // 일 -> sink 연결 : cap 1, cost 0
    for(int i = 1; i <= m; i++) {
        num = WORK_IDX + i;

        // 정방향 
        graph[num][SINK] = true; cap[num][SINK] = 1; flow[num][SINK] = 0; cost[num][SINK] = 0;
        // 역방향
        graph[SINK][num] = true; cap[SINK][num] = 0; flow[SINK][num] = 0; cost[SINK][num] = 0;
    }
}

int min_(int a, int b) {
    if(a > b) return b;
    return a;
}

void mcmf(int &work, int &pay) {
    // edmonds-karp + spfa
    while(true) {
        int parents[MAX_NODE]; // 증가 경로 계산용
        int dist[MAX_NODE]; // 최소 비용 경로 계산용 
        int queue[MAX_NODE]; // 전체 노드 들어가도 MAX_NODE개만큼 
        int head = -1;
        int tail = -1;
        int size = 0;
        bool inQueue[MAX_NODE]; // 큐에 있는지 여부 

        for(int i = 0; i < MAX_NODE; i++) {
            parents[i] = -1;
            dist[i] = INF;
            queue[i] = -1;
            inQueue[i] = false;
        }

        // source 추가 
        dist[SOURCE] = 0;
        queue[++tail] = SOURCE;
        head++;
        size++;
        inQueue[SOURCE] = true;

        // spfa
        while(size != 0) {
            int cur = queue[head];
            queue[head] = -1;
            head = (head + 1) % MAX_NODE;
            size--;
            inQueue[cur] = false;

            // cur 못 가는 곳 (처리 안 하면 계산 시 오버플로우)
            if(dist[cur] == INF) continue;

            for(int next = 0; next < MAX_NODE; next++) {
                // 연결 안 됨 
                if(graph[cur][next] == false) continue;

                // 용량 남아 있고, 최소 비용으로 가는 경우
                if((cap[cur][next] - flow[cur][next]) > 0) {
                    if(dist[next] > (dist[cur] + cost[cur][next])) {
                        // 업데이트할 거 처리
                        dist[next] = dist[cur] + cost[cur][next];
                        parents[next] = cur;

                        if(inQueue[next] == false) {
                            // 큐에 없을 때만 큐에 추가 (있으면 어짜피 나중에 돌게 됨)
                            tail = (tail + 1) % MAX_NODE;
                            queue[tail] = next;
                            size++;
                            inQueue[next] = true;
                        }
                    }
                }
            }
        }

        // 더 이상 증가 경로 없음
        if(parents[SINK] == -1) break;

        // 유량 계산 (증가 경로 상 최소값)
        int minFlow = INF;
        int node, parent;
        for(node = SINK; node != SOURCE; node = parent) {
            parent = parents[node];
            minFlow = min_(minFlow, cap[parent][node] - flow[parent][node]);
        }

        // 유량 추가 
        for(node = SINK; node != SOURCE; node = parent) {
            parent = parents[node];
            flow[parent][node] += minFlow;
            flow[node][parent] -= minFlow;
        }

        work += minFlow;
        pay += (dist[SINK] * minFlow); // 어짜피 계산된 유량은 모든 증가 경로 상에 동일하므로 개별로 안 더해도 됨
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    init();
    int work = 0;
    int pay = 0;
    mcmf(work, pay);

    // pay는 음수 처리하여 계산된 것
    pay *= -1;

    cout << work << '\n' << pay;
}
