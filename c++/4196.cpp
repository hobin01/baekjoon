#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

int T;
int N, M;
vector<int> graph[100001];
vector<int> invGraph[100001];
bool visited[100001];

// scc 중 indegree 0 인 거 개수가 정답 
// scc면 어짜피 그 안에서 아무거나 쓰러트려도 되고, scc 간 연결로 이어진 다른 scc도 쓰러짐 

void init() {
    cin >> N >> M;

    for(int i = 1; i <= N; i++) {
        graph[i].clear();
        invGraph[i].clear();
        visited[i] = false;
    }

    int to, from;
    for(int i = 0; i < M; i++) {
        cin >> to >> from;
        graph[to].push_back(from);
        invGraph[from].push_back(to);
    }
}

void dfs(int node, stack<int> &stk) {
    if(visited[node]) return;

    visited[node] = true;
    for(auto v : graph[node]) {
        if(visited[v]) continue;
        dfs(v, stk);
    }

    stk.push(node);
}

void invDfs(int node, vector<int> &vec) {
    if(visited[node]) return;

    visited[node] = true;
    vec.push_back(node);

    for(auto v : invGraph[node]) {
        if(visited[v]) continue;
        invDfs(v, vec);
    }
}

int calc() {
    int result = 0;

    memset(visited, false, sizeof(visited));
    stack<int> stk;
    for(int i = 1; i <= N; i++) {
        dfs(i, stk);
    }

    memset(visited, false, sizeof(visited));
    vector<vector<int>> scc;
    while(!stk.empty()) {
        int node = stk.top();
        stk.pop();

        vector<int> vec;
        invDfs(node, vec);
        if(vec.size() > 0) scc.push_back(vec);
    }

    // scc 1개면 통채로 사이클인 경우
    if(scc.size() == 1) {
        result = 1;
        return result;
    }

    // scc 구성된 것 중 indegree 0 인 거 구하기 
    // scc로 묶인 거는 같은 노드 간주
    // 기존에 엣지 기준으로 같은 노드 아니면 컴포넌트 간 엣지 있는 거
    vector<int> inDegree;
    inDegree.resize(scc.size());

    vector<int> components;
    components.resize(N + 1);

    // 몇 번째 컴포넌트인지 계산
    for(int i = 0; i < scc.size(); i++) {
        for(auto v : scc[i]) {
            components[v] = i;
        }
    }

    // 기존 엣지 대상으로 같은 컴포넌트인지 계산 
    for(int i = 1; i <= N; i++) {
        for(auto v : graph[i]) {
            if(components[i] != components[v]) {
                inDegree[components[v]]++;
            }
        }
    }

    // indegree 0 인 거 개수 
    for(auto v : inDegree) {
        if(v == 0) result++;
    }

    return result;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    while(T--) {
        init();
        int result = calc();
        cout << result << '\n';
    }
}
