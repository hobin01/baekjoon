#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

int n;
int inf = 987654321; // 모든 엣지 다 통과해도 70만

set<int> graph[52]; // A : 0 ~ Z : 25, a : 26 ~ z : 51
// graph[i] : i와 연결된 노드 집합
int cap[52][52]; // [i][j] -> i to j capacity (해당 엣지 용량)
int flow[52][52]; // [i][j] -> i to j flow (현재까지 계산된 유량)

int A = 0; // source
int Z = 25; // sink

int charToInt(char c) {
    if(c >= 'A' && c <= 'Z') return c - 'A';
    else return c - 'a' + 26;
}

void init() {

    for(int i = 0; i < 52; i++) {
        for(int j = 0; j < 52; j++) {
            cap[i][j] = 0;
            flow[i][j] = 0;
        }
    }

    cin >> n;

    char c1, c2;
    int v, node1, node2;
    for(int i = 0; i < n; i++) {
        cin >> c1 >> c2 >> v;
        node1 = charToInt(c1);
        node2 = charToInt(c2);

        graph[node1].insert(node2);
        graph[node2].insert(node1); // 문제 상 양방향 그래프 

        cap[node1][node2] += v; // 병렬로 연결 가능하므로 누적해서 cap 추가 
        cap[node2][node1] += v;
    }
}

int calc(int source, int sink) {
    // edmonds-karp

    int res = 0;

    while(true) {
        // 증가 경로 없을 때까지 반복

        vector<int> parents(52, -1); // 증가 경로 상 부모 없으면 -1 
        queue<int> q; // 증가 경로 계산 시 사용될 큐 (bfs)

        parents[source] = source;
        q.push(source);

        while(!q.empty() && (parents[sink] == -1)) {
            // 다 돌거나 sink 증가 경로에 포함되면 종료 

            int cur = q.front();
            q.pop();

            // 잔여 용량 있고 증가 경로에 포함 안 된 경우, 증가 경로에 추가 
            for(auto next : graph[cur]) {
                int remain = cap[cur][next] - flow[cur][next];
                if((remain > 0) && (parents[next] == -1)) {
                    q.push(next);
                    parents[next] = cur;
                }
            }
        }

        // sink 증가 경로에 없음. 즉, 더 이상 증가 경로 없음 
        if(parents[sink] == -1) break;

        // 증가 경로 중 잔여 용량 최소값만큼 유량 추가 
        int node = sink;
        int p; // 부모 노드 계산용 
        int amount = inf;
        while(node != source) {
            p = parents[node];
            amount = min(amount, cap[p][node] - flow[p][node]);
            node = p;
        }

        // 계산된 유량 추가
        node = sink;
        while(node != source) {
            p = parents[node];
            flow[p][node] += amount;
            flow[node][p] -= amount; 
            node = p;
        }

        // 전체 유량에 추가 
        res += amount;
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    init();
    cout << calc(A, Z);
}
