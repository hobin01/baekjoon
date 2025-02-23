#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// state x == T : x 뺀다 F : x 그대로 둔다
// (a or b) == T : a 또는 b를 뺀다 
// 겹치는 거 대상으로 CNF 구성
// 각 사람은 3개 중 최대 1개 뺄 수 있으므로 ~(a and b) == T : a, b 모두 그대로 둔다
// 이므로 (~a or ~b) and (~a or ~c) and (~b or ~c) == T : a, b, c 중 최대 1개만 뺀다 

// 2-sat : a or b == ~a -> b / ~b -> a
// 입력값 대상으로 겹치는 거 + 본인 거 대상으로 그래프 생성

// 겹치는 지 유무 : ccw로 체크 (외적 방향 다르면 겹치는 거)

int N;
int MAX_N = 3000;
pair<pair<int, int>, pair<int, int>> sticks[3001];
vector<int> graph[6001];
vector<int> invGraph[6001];
bool visited[6001];
bool invVisited[6001];
stack<int> stk;
int sccIdx[6001];

void init() {
    cin >> N;
    int x1, y1, x2, y2;
    for(int i = 1; i <= 3 * N; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        sticks[i] = {{x1, y1}, {x2, y2}};
    }
}

void makeGraphWithOwnSticks() {
    // 자기가 갖고 있는 거 대상으로 그래프 그리기 
    // (~a or ~b) and (~a or ~c) and (~b or ~c)
    // a or b == ~a -> b / ~b -> a
    // ~a or ~b == a -> ~b / b -> ~a
    int a, b, c, na, nb, nc;
    for(int i = 1; i <= 3 * N; i += 3) {
        a = i;
        na = MAX_N + a;
        b = i + 1;
        nb = MAX_N + b;
        c = i + 2;
        nc = MAX_N + c;

        // ~a or ~b
        graph[a].push_back(nb);
        invGraph[nb].push_back(a);
        graph[b].push_back(na);
        invGraph[na].push_back(b);

        // ~b or ~c
        graph[b].push_back(nc);
        invGraph[nc].push_back(b);
        graph[c].push_back(nb);
        invGraph[nb].push_back(c);

        // ~c or ~a
        graph[c].push_back(na);
        invGraph[na].push_back(c);
        graph[a].push_back(nc);
        invGraph[nc].push_back(a);
    }
}

bool CCW(pair<pair<int, int>, pair<int, int>> &p1, pair<pair<int, int>, pair<int, int>> &p2) {
    // p1 기준, p2 대상으로 외적, p2 기준, p1 대상으로 외적 계산해서
    // 모두 다른 방향이면 겹치는 거 
    // 2차원이므로 z 빼고 계산해도 됨. 그리고 일직선인 케이스는 신경 안 써도 됨 (입력에 없음)

    // p1 기준
    pair<int, int> v1 = {p1.second.first - p1.first.first, p1.second.second - p1.first.second};
    pair<int, int> v2 = {p2.second.first - p1.second.first, p2.second.second - p1.second.second};
    pair<int, int> v3 = {p2.first.first - p1.second.first, p2.first.second - p1.second.second};

    bool chk1 = ((v1.first * v2.second) - (v1.second * v2.first) > 0);
    bool chk2 = ((v1.first * v3.second) - (v1.second * v3.first) > 0);

    // 같으면 안 겹침 
    if(chk1 == chk2) return false;

    // p2 기준 
    v1 = {p2.second.first - p2.first.first, p2.second.second - p2.first.second};
    v2 = {p1.second.first - p2.second.first, p1.second.second - p2.second.second};
    v3 = {p1.first.first - p2.second.first, p1.first.second - p2.second.second};

    chk1 = ((v1.first * v2.second) - (v1.second * v2.first) > 0);
    chk2 = ((v1.first * v3.second) - (v1.second * v3.first) > 0);

    if(chk1 == chk2) return false;

    return true;
}

void makeGraphWithCrossedSticks() {
    // 겹치는 거 대상으로 그래프 추가
    // a or b == ~a -> b / ~b -> a
    int a, b, na, nb;
    for(int i = 1; i <= 3 * N; i++) {
        for(int j = i + 1; j <= 3 * N; j++) {
            bool isCrossed = CCW(sticks[i], sticks[j]);
            if(isCrossed == false) continue;

            a = i;
            b = j;
            na = MAX_N + a;
            nb = MAX_N + b;

            // ~a -> b
            graph[na].push_back(b);
            invGraph[b].push_back(na);
            // ~b -> a 
            graph[nb].push_back(a);
            invGraph[a].push_back(nb);
        }
    }
}

void makeGraph() {
    makeGraphWithOwnSticks();
    makeGraphWithCrossedSticks();
}

void dfs(int node) {
    if(visited[node]) return;
    
    visited[node] = true;
    for(auto v : graph[node]) {
        if(visited[v]) continue;
        dfs(v);
    }

    stk.push(node);
}

void invDfs(int node, int idx) {
    if(invVisited[node]) return;

    invVisited[node] = true;
    sccIdx[node] = idx;

    for(auto v : invGraph[node]) {
        if(invVisited[v]) continue;
        invDfs(v, idx);
    }
}

void SCC() {
    // 스택에 촥촥
    for(int i = 1; i <= 3 * N; i++) {
        dfs(i);
        dfs(MAX_N + i);
    }

    // 스택에 있는 거 대상으로 scc 만들기 
    // idx : scc idx
    int idx = 0;
    while(!stk.empty()) {
        int node = stk.top();
        stk.pop();

        if(invVisited[node]) continue;

        invDfs(node, idx);
        idx++;
    }
}

void calc() {
    // scc 구한 거 대상으로 x, ~x 같은 scc면 모순이므로 안 되는 케이스
    // 그런 거 없으면 위상정렬 순으로 x -> ~x : x = false, ~x -> x : x = true 
    int x, nx;
    for(int i = 1; i <= 3 * N; i++) {
        x = i;
        nx = MAX_N + x;
        if(sccIdx[x] == sccIdx[nx]) {
            cout << -1;
            return;
        }
    }

    vector<int> result;

    for(int i = 1; i <= 3 * N; i++) {
        x = i;
        nx = MAX_N + x;
        if(sccIdx[x] < sccIdx[nx]) {
            // x = false case 
            continue;
        } else {
            // x = true case 
            result.push_back(x);
        }
    }

    cout << result.size() << '\n';
    for(auto v : result) {
        cout << v << ' ';
    }
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    makeGraph();
    SCC();
    calc();
}
