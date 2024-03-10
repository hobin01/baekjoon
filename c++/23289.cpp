#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

// 1. 바람 나옴
// 2. 온도 조절
// 3. 바깥쪽 온도 1 감소 (0 제외)
// 4. 초콜릿 먹음 
// 5. 조사칸 모든 온도 K 이상인지 체크 

int R, C, K, W;

struct room {
    int temp = 0; // 현재 온도 
    bool walls[4] = {false,}; // 벽 유무 (0,1,2,3 : 상하좌우)
};
struct robot {
    int y;
    int x;
    int dir; // 로봇 방향 1~4 : 오, 왼, 위, 아래
};
struct check_loc {
    int y;
    int x;
};

room map[21][21];
vector<robot> robots;
vector<check_loc> check_locs;

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

void init()
{
    cin >> R >> C >> K;
    
    int num;
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            cin >> num;
            if(num != 0 && num != 5) {
                robot r = {i, j, num};
                robots.push_back(r);
            }
            else if(num == 5) {
                check_loc c = {i, j};
                check_locs.push_back(c);
            }
        }
    }
    
    cin >> W;
    
    int y, x, t;
    for(int i = 0; i < W; i++) {
        cin >> y >> x >> t;
        if(t == 0) {
            map[y][x].walls[0] = true;
            if((y-1) >= 1)
                map[y-1][x].walls[1] = true;
        }
        else {
            map[y][x].walls[3] = true;
            if((x+1) <= C)
                map[y][x+1].walls[2] = true;
        }
    }
}

void get_wind(robot r)
{
    int dir = -1;
    switch(r.dir) {
        case 1: dir = 3; break;
        case 2: dir = 2; break;
        case 3: dir = 0; break;
        case 4: dir = 1; break;
        default: break;
    }
    
    // 바람 진행 못하는 경우 
    int y, x, ny, nx, v;
    
    y = r.y;
    x = r.x;
    ny = y + dy[dir];
    nx = x + dx[dir];
    
    if(ny <= 0 || nx <= 0 || ny > R || nx > C) {
        return;
    }
    if(map[y][x].walls[dir])
        return;
    
    //  바람 위치, 값 
    queue<pair<pair<int, int>, int>> q;
    bool visited[21][21];
    for(int i = 1; i <= R; i++) {
        memset(visited[i], false, sizeof(visited[i]));
    }
    
    y = ny;
    x = nx;
    q.push({{y, x}, 5});
    
    visited[y][x] = true;
    
    while(!q.empty()) {
        y = q.front().first.first;
        x = q.front().first.second;
        v = q.front().second;
        q.pop();
        
        map[y][x].temp += v;
        
        // v=1 이면 더 이상 진행 안 해도 됨 
        if(v == 1)
            continue;
        
        // 방향 그대로 
        ny = y + dy[dir];
        nx = x + dx[dir];
        
        if(ny >= 1 && nx >= 1 && ny <= R && nx <= C) {
            if(!visited[ny][nx] && !map[y][x].walls[dir]) {
                q.push({{ny, nx}, v-1});
                visited[ny][nx] = true;
            }
        }
        
        if(dir == 0) {
            // 대각선 1 
            // 좌 후 상 
            ny = y - 1;
            nx = x - 1;
            if(ny >= 1 && nx >= 1 && ny <= R && nx <= C) {
                if(!visited[ny][nx] && !map[y][x].walls[2] && !map[ny][nx].walls[1]) {
                    q.push({{ny, nx}, v-1});
                    visited[ny][nx] = true;
                }
            }
            // 대각선 2 
            // 우 후 상 
            ny = y - 1;
            nx = x + 1;
            if(ny >= 1 && nx >= 1 && ny <= R && nx <= C) {
                if(!visited[ny][nx] && !map[y][x].walls[3] && !map[ny][nx].walls[1]) {
                    q.push({{ny, nx}, v-1});
                    visited[ny][nx] = true;
                }
            }
        }
        else if(dir == 1) {
            // 대각선 1 
            // 좌 후 하
            ny = y + 1;
            nx = x - 1;
            if(ny >= 1 && nx >= 1 && ny <= R && nx <= C) {
                if(!visited[ny][nx] && !map[y][x].walls[2] && !map[ny][nx].walls[0]) {
                    q.push({{ny, nx}, v-1});
                    visited[ny][nx] = true;
                }
            }
            // 대각선 2 
            // 우 후 하   
            ny = y + 1;
            nx = x + 1;
            if(ny >= 1 && nx >= 1 && ny <= R && nx <= C) {
                if(!visited[ny][nx] && !map[y][x].walls[3] && !map[ny][nx].walls[0]) {
                    q.push({{ny, nx}, v-1});
                    visited[ny][nx] = true;
                }
            }
        }
        else if(dir == 2) {
            // 대각선 1 
            // 상 후 좌 
            ny = y - 1;
            nx = x - 1;
            if(ny >= 1 && nx >= 1 && ny <= R && nx <= C) {
                if(!visited[ny][nx] && !map[y][x].walls[0] && !map[ny][nx].walls[3]) {
                    q.push({{ny, nx}, v-1});
                    visited[ny][nx] = true;
                }
            }
            // 대각선 2 
            // 하 후 좌   
            ny = y + 1;
            nx = x - 1;
            if(ny >= 1 && nx >= 1 && ny <= R && nx <= C) {
                if(!visited[ny][nx] && !map[y][x].walls[1] && !map[ny][nx].walls[3]) {
                    q.push({{ny, nx}, v-1});
                    visited[ny][nx] = true;
                }
            }
        }
        else if(dir == 3) {
            // 대각선 1 
            // 상 후 우  
            ny = y - 1;
            nx = x + 1;
            if(ny >= 1 && nx >= 1 && ny <= R && nx <= C) {
                if(!visited[ny][nx] && !map[y][x].walls[0] && !map[ny][nx].walls[2]) {
                    q.push({{ny, nx}, v-1});
                    visited[ny][nx] = true;
                }
            }
            // 대각선 2 
            // 하 후 우 
            ny = y + 1;
            nx = x + 1;
            if(ny >= 1 && nx >= 1 && ny <= R && nx <= C) {
                if(!visited[ny][nx] && !map[y][x].walls[1] && !map[ny][nx].walls[2]) {
                    q.push({{ny, nx}, v-1});
                    visited[ny][nx] = true;
                }
            }
        }
    }
}

void control_temp()
{
    pair<int, int> temp_map[21][21]; // {올릴 값, 내릴 값}
    int y, x, ny, nx, temp, ntemp, diff;
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            temp_map[i][j] = {0, 0};
            
            for(int k = 0; k < 4; k++) {
                y = i; x = j;
                ny = y + dy[k];
                nx = x + dx[k];
                
                if(ny <= 0 || nx <= 0 || ny > R || nx > C)
                    continue;
                if(map[y][x].walls[k])
                    continue;
                
                temp = map[y][x].temp;
                ntemp = map[ny][nx].temp;
                
                diff = (ntemp - temp) / 4;
                if(diff > 0) {
                    temp_map[y][x].first += diff;
                }
                else if(diff < 0) {
                    temp_map[y][x].second += (-1 * diff);
                }
            }
        }
    }
    
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            map[i][j].temp += temp_map[i][j].first;
            map[i][j].temp -= temp_map[i][j].second;
        }
    }
}

void control_outside()
{
    for(int y = 1; y <= R; y++) {
        if(map[y][1].temp >= 1)
            map[y][1].temp--;
        if(map[y][C].temp >= 1)
            map[y][C].temp--;
    }
    for(int x = 2; x < C; x++) {
        if(map[1][x].temp >= 1)
            map[1][x].temp--;
        if(map[R][x].temp >= 1)
            map[R][x].temp--;
    }
}

bool check_temp()
{
    bool res = true;
    for(auto c : check_locs) {
        if(map[c.y][c.x].temp < K) {
            res = false;
            break;
        }
    }
    return res;
}

void game()
{
    int result = 0;
    
    while(true) {
        if(result == 100) {
            result = 101;
            break;
        }
        
        for(auto r : robots) {
            get_wind(r);
        }
        
        control_temp();
        control_outside();
        result++;
        
        if(check_temp()) {
            break;
        }
    }
    
    cout << result;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    init();
    game();
}
