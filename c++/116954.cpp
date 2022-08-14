#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// 벽 : 1초마다 1칸 아래로 이동, 마지막 행에서 이동 시 사라짐
// 욱제 : 인접칸, 대각선, 가만히 가능 
// 욱제 먼저 이동, 벽 이동 
// 욱제 : 왼 아래 => 오 위 이동 가능 여부 확인

// 가만히, 상하좌우, 오른 위, 왼 위, 왼 아래, 오른 아래 순
int dx[9] = {0, 0, 0, -1, 1, 1, -1, -1, 1};
int dy[9] = {0, -1, 1, 0, 0, -1, -1, 1, 1};

// . 빈칸, # 벽 
// 판 : 8x8
// 벽이 욱제 위치로 이동하면 종료

char board[8][8];
pair<int,int>start = {7, 0}; // (y, x)순
pair<int,int>last  = {0, 7};

vector<pair<int,int>> vec; // 벽 위치 

void init()
{
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            cin >> board[i][j];
            if(board[i][j] == '#') {
                vec.push_back({i, j});
            }
        }
    }
    
}

int bfs()
{
    queue< pair<pair<int,int>, vector<pair<int,int>> > >q;
    // 욱제 위치, 벽 위치 
    q.push({start, vec});
    
    int res = 0; // 도착 여부 
    
    pair<int,int>loc;
    vector<pair<int,int>> wall;
    vector<pair<int, int>> nwall;
    
    while(!q.empty()) {
        wall.clear();
        wall.shrink_to_fit();
        nwall.clear();
        nwall.shrink_to_fit();
        
        loc = q.front().first;
        wall = q.front().second;
        
        q.pop();
        
        // 도착 여부 확인 
        if(loc.first == last.first && loc.second == last.second) {
            res = 1;
            break;
        }
        // 벽 없으면 무조건 감
        if(wall.size() == 0) {
            res = 1;
            break;
        }
        
        // 벽 이동할 위치 
        for(auto w : wall) {
            int nwy = w.first + 1;
            int nwx = w.second;
            
            if(nwy >= 8)
                continue;
            
            nwall.push_back({nwy, nwx});
        }
        
        for(int i = 0; i < 9; i++) {
            int ny = loc.first + dy[i];
            int nx = loc.second + dx[i];
            
            if(ny < 0 || ny >= 8 || nx < 0 || nx >= 8)
                continue;
            
            bool isWall = false;
            for(auto w : wall) {
                // 이동하는 곳에 벽
                if(w.first == ny && w.second  == nx) {
                    isWall = true;
                    break;
                }
                // 벽에 가로막힐 예정
                if(ny - 1 == w.first && nx == w.second) {
                    isWall = true;
                    break;
                }
            }
            
            if(isWall)
                continue;
            
            // 새 욱제 위치     
            pair<int, int> nloc = {ny, nx};
            
            q.push({nloc, nwall});
        }
    }
    
    return res;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    
    init();
    cout << bfs();
}