#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;

int N, M;
// 음수에 대한 인덱스 계산을 위해 아래와 같이 인덱스 부여 
// a > 0: a<<1, a < 0 : a<<1 | 1

// a or b == (~a -> b) / (~b -> a)

vector<int> graph[10001 << 1];
vector<int> invGraph[10001 << 1];
bool visited[10001 << 1];
bool invVisited[10001 << 1];
vector<vector<int>> scc;
int sccIdx[10001 << 1];
stack<int> stk;

void init() {
    cin >> N >> M;
    int A, B;
    int a, b, na, nb;
    for(int i = 0; i < M; i++) {
        cin >> A >> B;
        if(A > 0) {
            a = A << 1;
            na = A << 1 | 1;
        } else {
            a = -A << 1 | 1;
            na = -A << 1;
        }

        if(B > 0) {
            b = B << 1;
            nb = B << 1 | 1;
        } else {
            b = -B << 1 | 1;
            nb = -B << 1;
        }

        graph[na].push_back(b);
        invGraph[b].push_back(na);
        graph[nb].push_back(a);
        invGraph[a].push_back(nb);
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
    for(int node = 1; node <= (N << 1 | 1); node++) {
        dfs(node);
    }

    int idx = 0;
    while(!stk.empty()) {
        int node = stk.top();
        stk.pop();

        vector<int> vec;
        invDfs(node, vec);

        if(!vec.empty()) {
            scc.push_back(vec);
            for(auto v : vec) {
                sccIdx[v] = idx;
            }
            idx++;
        }
    }
}

bool calc() {
    // x, ~x 같이 있으면 false, 아니면 true
    for(int i = 1; i <= N; i++) {
        if(sccIdx[i << 1] == sccIdx[i << 1 | 1])
            return false;
    }
    return true;
}

void getAnswer() {
    vector<bool> answer(N+1, false);

    for(int node = 1; node <= N; node++) {
        if(sccIdx[node << 1] < sccIdx[node << 1 | 1]) {
            // x -> ~x : x = false
            answer[node] = false;
        } else {
            // ~x -> x : x = true 
            answer[node] = true;
        }
    }

    for(int i = 1; i <= N; i++) {
        cout << answer[i] << ' ';
    }
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();
    getSCC();
    if(calc() == false) {
        cout << 0;
    } else {
        cout << 1 << '\n';
        getAnswer();
    }
    return 0;
}
