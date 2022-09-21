#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int map[51][51];
// H 대신 0으로 처리
int n, m;
bool inf;

// 상하좌우
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, 1, -1};

int dp[51][51]; // dp로 y,x 위치까지 탐색했을 때 최대값 계산
bool visited[51][51]; // 방문 여부 확인 (루프 체크 )

void init()
{
    cin >> n >> m;
    
    string s;
    for(int i = 0; i < n; i++) {
        cin >> s;
        for(int j = 0; j < s.size(); j++) {
            if(s[j] == 'H') {
                map[i][j] = 0;
            }
            else {
                map[i][j] = s[j] - '0';
            }
            dp[i][j] = -1;
            visited[i][j] = false;
        }
    }
    
    inf = false; // 무한루프 체크용 
}

// dfs 돌면서 지나온 애들 다 저장
// 만약 돈 지점 도착 시 무한루프 발생
// 그거 아니면 정답 후보

int dfs(pair<int, int> p)
{
    // p : 현재 위치, cnt : 현재까지 카운트된 횟수, vec : 지나온 위치 
    
    // 밖인 경우 
    if(p.first < 0 || p.first >= n || p.second < 0 || p.second >= m) {
        return 0;
    }
    
    // 구명인 경우 
    int x = map[p.first][p.second];
    if(x == 0) {
        return 0;
    }
    
    // 현재 지나온 길에 있는 경우
    if(visited[p.first][p.second]) {
        inf = true;
        return 0;
    }
    
    // 이미 계산된 경우 
    if(dp[p.first][p.second] != -1)
        return dp[p.first][p.second];
    
    visited[p.first][p.second] = true;
    
    // 이동 가능한 경우
    for(int i = 0; i < 4; i++) {
        int ny = p.first + dy[i] * x;
        int nx = p.second + dx[i] * x;
        
        pair<int,int> np = {ny, nx};
        
        dp[p.first][p.second] = max(dp[p.first][p.second], dfs(np) + 1);
    }
    
    visited[p.first][p.second] = false; // 다음 방향 돌려고 초기화 
    
    return dp[p.first][p.second];
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    pair<int,int> start = {0, 0};
    int result = dfs(start);
    
    if(inf) {
        cout << -1;
    }
    else {
        cout << result;
    }
    
}