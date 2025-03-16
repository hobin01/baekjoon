#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <cstring>
#include <set>

using namespace std;

// SCC + SPFA (edge 개수 == node 개수 이므로 선형 동작)
// 합 최대 20억 

int N, M;
const int MAX_N = 500001;

vector<int> graph[MAX_N];
vector<int> invGraph[MAX_N];
stack<int> stk;
int scc[MAX_N]; // scc index 기록용 
bool visited[MAX_N];
bool invVisited[MAX_N];

int start; // 시작 지점 
int totalCurry; // 총 식당 개수 
int cash[MAX_N]; // 각 지점 현금 
bool isCurry[MAX_N]; // 식당 여부

vector<int> sccGraph[MAX_N]; // scc 간 그래프 
int sccCash[MAX_N]; // scc로 묶인 cash 합 
int sccDp[MAX_N]; // scc 각 지점까지 모을 수 있는 최대값 저장용 (연결된 노드 dp 값 + 해당 노드 값 중 최대값)
bool inQueue[MAX_N];

void init() {
    cin >> N >> M;
    int from, to;
    for(int i = 0; i < M; i++) {
        cin >> from >> to;
        graph[from].push_back(to);
        invGraph[to].push_back(from);
    }
    for(int i = 1; i <= N; i++) {
        cin >> cash[i];
    }
    cin >> start >> totalCurry;
    
    int curry; // 식당
    for(int i = 0; i < totalCurry; i++) {
        cin >> curry;
        isCurry[curry] = true;
    }

    // dp 초기화 (-1 : 아직 계산 안 됨)
    for(int i = 1; i <= N; i++) {
        sccDp[i] = -1;
    }
}

void dfs(int node) {
    if(visited[node]) return;
    visited[node] = true;

    for(auto v : graph[node]) {
        if(visited[v]) continue;
        dfs(v);
    }

    stk.push(node);
    return;
}

void invDfs(int node, vector<int> &vec) {
    // vec : scc로 연결된 애들 
    if(invVisited[node]) return;
    invVisited[node] = true;

    vec.push_back(node);
    for(auto v : invGraph[node]) {
        if(invVisited[v]) continue;
        invDfs(v, vec);
    }

    return;
}

void getSCC() {
    for(int node = 1; node <= N; node++) {
        dfs(node);
    }

    int idx = 0;
    while(!stk.empty()) {
        int node = stk.top();
        stk.pop();
        vector<int> vec;

        // 같은 scc에 있는 건 cash 모으는 거 동일함 
        int totalCash = 0;
        invDfs(node, vec);
        for(auto v : vec) {
            scc[v] = idx;
            totalCash += cash[v];
        }
        sccCash[idx] = totalCash;
        idx++;
    }

    // scc 간 그래프 만들기 (edge 최대 50만)
    // set vs 중복해서 넣기 해보니 중복이 더 빠름 
    int totalSCC = idx;
    bool sccVisited[totalSCC];
    memset(sccVisited, false, sizeof(sccVisited));

    for(int i = 1; i <= N; i++) {
        for(auto v : graph[i]) {
            if(scc[i] != scc[v] && sccVisited[scc[v]] == false) {
                sccGraph[scc[i]].push_back(scc[v]);
                sccVisited[scc[v]] = true;
            }
        }

        for(auto v : sccGraph[scc[i]]) {
            sccVisited[v] = false;
        }
    }
}

int calc() {
    int res = -1;

    // SPFA 계산 
    queue<int> q;
    int startIdx = scc[start];
    q.push(startIdx);
    inQueue[startIdx] = true;
    sccDp[startIdx] = sccCash[startIdx];

    while(!q.empty()) {
        int idx = q.front();
        q.pop();
        inQueue[idx] = false;

        // idx번째 scc까지 가는 경로 없음 
        if(sccDp[idx] == -1) continue; 

        for(auto nextIdx : sccGraph[idx]) {
            if(sccDp[nextIdx] == -1 || (sccDp[nextIdx] < (sccDp[idx] + sccCash[nextIdx]))) {
                sccDp[nextIdx] = sccDp[idx] + sccCash[nextIdx];
                if(inQueue[nextIdx] == false) {
                    inQueue[nextIdx] = true;
                    q.push(nextIdx);
                }
            }
        }
    }

    // 각 scc에 식당 있는 경우 중, dp 값 최대값이 정답 
    for(int i = 1; i <= N; i++) {
        if(isCurry[i]) {
            res = max(res, sccDp[scc[i]]);
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    init();
    getSCC();
    cout << calc();
}
