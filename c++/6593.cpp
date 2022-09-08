#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>

using namespace std;

int L, R, C;
int MoveTime[31][31][31]; // {z, y, x} 위치까지 도달하는 최단 시간
char Building[31][31][31]; // 빌딩 모습
bool check[31][31][31]; // 도착 여부 확인 

int inf = 987654321; // 모든 칸 다 돌아도 최대 30 * 30 * 30

struct loc {
    int z;
    int y;
    int x;
};

loc S; // start
loc E; // end 

int dx[6] = {1,-1,0,0,0,0};
int dy[6] = {0,0,1,-1,0,0};
int dz[6] = {0,0,0,0,1,-1}; // 동서남북상하

void printAnswer(int x)
{
    if(x == inf)
        cout << "Trapped!" << '\n';
    else 
        cout << "Escaped in " << x << " minute(s)." << '\n';
}

void init()
{
    for(int i = 1; i <= L; i++) {
        for(int j = 1; j <= R; j++) {
            for(int k = 1; k <= C; k++) {
                MoveTime[i][j][k] = inf;
                check[i][j][k] = false;
            }
        }
    }
    
    for(int i = 1; i <= L; i++) {
        for(int j = 1; j <= R; j++) {
            string s;
            cin >> s;
            for(int k = 1; k <= C; k++) {
                Building[i][j][k] = s[k - 1];
                if(s[k - 1] == 'S') {
                    S = {i, j, k};
                }
                else if(s[k - 1] == 'E') {
                    E = {i, j, k};
                }
            }
        }
    }
}

void bfs()
{
    queue< pair<loc, int> > q;
    q.push({S, 0});
    MoveTime[S.z][S.y][S.x] = 0;
    check[S.z][S.y][S.x] = true;
    
    while(!q.empty()) {
        loc p = q.front().first;
        int t = q.front().second;
        q.pop();
        
        for(int i = 0; i < 6; i++) {
            int nz = p.z + dz[i];
            int ny = p.y + dy[i];
            int nx = p.x + dx[i];
            
            // 벗어남
            if(nz < 1 || nz > L || ny < 1 || ny > R || nx < 1 || nx > C) 
                continue;
            // 벽
            if(Building[nz][ny][nx] == '#')
                continue;
            // 방문한 적 없음
            if(check[nz][ny][nx] == false) {
                check[nz][ny][nx] = true;
                MoveTime[nz][ny][nx] = t + 1;
                q.push({{nz, ny, nx}, t + 1});
            }
            // 방문한 적 있음
            else {
                int prevTime = MoveTime[nz][ny][nx];
                if(prevTime > (t + 1)) {
                    MoveTime[nz][ny][nx] = t + 1;
                    q.push({{nz, ny, nx}, t + 1});
                }
            }
        }
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    while(true) {
        cin >> L >> R >> C;
        if(L == 0 && R == 0 && C == 0)
            break;
            
        init();
        bfs();
        int ans = MoveTime[E.z][E.y][E.x];
        printAnswer(ans);
    }
}