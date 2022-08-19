#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m;
vector<int> parent[2001]; // i번 노드의 부모들 
vector<int> child[2001]; // i번 노드의 자식들
int meet[2001];
bool visited[2001];

// 큰 게 부모, 작은 게 자식 가정
// 자식 방향, 부모 방향으로 계속 탐색
// 만나는 애들 카운트

void init()
{
    cin >> n;
    cin >> m;
    int p, c;
    for(int i = 0; i < m; i++) {
        cin >> p >> c;
        child[p].push_back(c);
        parent[c].push_back(p);
    }
    
    memset(visited, false, sizeof(visited));
    memset(meet, 0, sizeof(meet));
}

void init_visit()
{
    memset(visited, false, sizeof(visited));
}

void child_dfs(int start, int node)
{
    visited[node] = true;
    
    for(auto c : child[node]) {
        if(visited[c])
            continue;
        meet[start]++;
        child_dfs(start, c);
    }
}

void parent_dfs(int start, int node)
{
    visited[node] = true;
    
    for(auto p : parent[node]) {
        if(visited[p])
            continue;
        meet[start]++;
        parent_dfs(start, p);
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    
    for(int i = 1; i <= n; i++) {
        init_visit();
        child_dfs(i, i);
        parent_dfs(i, i);
        
        cout << n - meet[i] - 1 << '\n';
    }
}