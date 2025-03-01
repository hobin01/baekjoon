#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int INF = 987654321;

vector<vector<int>> edges; // 왼쪽 (사람) 기준, 연결된 오른쪽 (일)
vector<int> dist; // 왼쪽 정점 거리 (bfs용)
vector<int> matchL; // 왼쪽 정점과 매칭된 오른쪽 정점 (0 : nil)
vector<int> matchR; // 오른쪽 정점과 매칭된 왼쪽 정점 

void init() {
    cin >> N >> M;
    edges.resize(2 * N + 1);
    dist.resize(2 * N + 1);
    matchL.resize(2 * N + 1);
    matchR.resize(M + 1);

    int work, num;
    for(int i = 1; i <= 2 * N; i+=2) {
        cin >> work;
        while(work--) {
            // 복제인간 있다 치고 같은 사람 2명 놨을 떄 이분 매칭이랑 동일 (최대 2개 담당)
            cin >> num;
            edges[i].push_back(num);
            edges[i+1].push_back(num);
        }
    }
}

bool bfs() {
    // 증강 경로 레벨 설정 
    // nil (0) 까지 도달하는 경로 있으면 증강 경로 있는 거, 없으면 없는 거 
    queue<int> q;
    dist[0] = INF;

    for(int u = 1; u <= 2 * N; u++) {
        if(matchL[u] == 0) {
            // 아직 매칭 없는 왼쪽 정점
            dist[u] = 0;
            q.push(u);
        } else {
            dist[u] = INF;
        }
    }

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        // 증강 거리 계산 
        // 오른쪽이 매칭되어 있으면, 매칭된 왼쪽 정점 거리를 현재 왼쪽 정점 거리보다 1 크게 설정 
        if(dist[u] < dist[0]) {
            for(auto v : edges[u]) {
                int matched = matchR[v];
                if(dist[matched] == INF) {
                    dist[matched] = dist[u] + 1;
                    q.push(matched);
                }
            }
        }
    }

    return dist[0] != INF;
}

bool dfs(int u) {
    // u에서 시작하는 증강 경로 찾음 
    if(u == 0) return true;

    for(auto v : edges[u]) {
        int matched = matchR[v];
        if(dist[matched] == (dist[u] + 1) && dfs(matched)) {
            // 증강 경로 있는 경우, 매칭 반전 
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }

    // 더 이상 증강 경로 없음 
    dist[u] = INF;
    return false;
}

int calc() {
    // 최대 매칭 개수 찾기 
    int result = 0;
    while(bfs()) {
        for(int u = 1; u <= 2 * N; u++) {
            if(matchL[u] == 0 && dfs(u)) result++;
        }
    }

    return result;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    init();
    cout << calc();
}
