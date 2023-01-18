#include <iostream>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

int n, m;
char map[11][11]; // 최대 10 * 10
bool visited[11][11][11][11];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

pair<int, int> red;
pair<int, int> blue;

int result;

void init()
{
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> map[i][j];
            if(map[i][j] == 'R') {
                red = {i, j};
            }
            if(map[i][j] == 'B') {
                blue = {i, j};
            }
        }
    }
    
    memset(visited, false, sizeof(visited));
    result = 0;
}

void bfs()
{
    // {{빨강 위치}, {파랑 위치}}
    queue<pair<pair<int, int>, pair<int, int>> > q;
    
    q.push({red, blue});
    visited[red.first][red.second][blue.first][blue.second] = true;
    
    bool success = false;
    
    while(!q.empty()) {
        int s = q.size();
        
        // 굴릴 수 있는 모든 경우 해보기
        while(s--) {
            int ry = q.front().first.first;
            int rx = q.front().first.second;
            int by = q.front().second.first;
            int bx = q.front().second.second;
            
            q.pop();
            
            // 성공하는 경우 
            if(map[ry][rx] == 'O' && map[ry][rx] != map[by][bx]) {
                success = true;
                break;
            }
            
            // 굴리기
            for(int i = 0; i < 4; i++) {
                int rny = ry;
                int rnx = rx;
                int bny = by;
                int bnx = bx;
                
                // 구멍 만나면 멈추도록 하고 다음 루프 때 탈출시키기 (단 파랑 주의)
                while(map[rny + dy[i]][rnx + dx[i]] != '#' && map[rny][rnx] != 'O') {
                    rny += dy[i];
                    rnx += dx[i];
                }
                while(map[bny + dy[i]][bnx + dx[i]] != '#' && map[bny][bnx] != 'O') {
                    bny += dy[i];
                    bnx += dx[i];
                }
                
                // 파랑 빨강 겹치면 원래 방향대로 한 칸 뒤로
                if(rny == bny && rnx == bnx) {
                    // 구멍 빠짐
                    if(map[rny][rnx] == 'O')
                        continue;
                    
                    // 움직인 거리 구하기
                    int rdy = abs(rny - ry);
                    int rdx = abs(rnx - rx);
                    int bdy = abs(bny - by);
                    int bdx = abs(bnx - bx);
                    
                    // 택시 norm
                    if(rdy + rdx < bdy + bdx) {
                        bny -= dy[i];
                        bnx -= dx[i];
                    }
                    else {
                        rny -= dy[i];
                        rnx -= dx[i];
                    }
                }
                
                // 방문 여부 체크
                if(visited[rny][rnx][bny][bnx] == false) {
                    q.push({{rny, rnx}, {bny, bnx}});
                    visited[rny][rnx][bny][bnx] = true;
                }
            }
        }
        
        // 끝
        if(success)
            break;
        else
            result++;
    }
    
    if(success)
        cout << result;
    else
        cout << -1;
}

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(NULL); 
	cout.tie(NULL);
	
    init();
    bfs();
}