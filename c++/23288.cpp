#include <iostream>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;

int n, m, k;
int map[21][21];
int score[21][21];
bool visited[21][21];
int result;

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

struct Dice {
    int up;
    int down;
    int east;
    int west;
    int south;
    int north;
};

Dice dice;

void init()
{
    cin >> n >> m >> k;
    memset(map, 0, sizeof(map));
    memset(score, 0, sizeof(score));
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> map[i][j];
        }
    }
    
    dice = {1, 6, 3, 4, 5, 2};
    result = 0;
}

Dice roll_dice(Dice d, char c)
{
    // c : u, d, l, r
    // up, down, left, right
    Dice res;
    
    if(c == 'u') {
        res.up = d.south;
        res.down = d.north;
        res.east = d.east;
        res.west = d.west;
        res.south = d.down;
        res.north = d.up;
    }
    
    else if(c == 'd') {
        res.up = d.north;
        res.down = d.south;
        res.east = d.east;
        res.west = d.west;
        res.south = d.up;
        res.north = d.down;
    }
    
    else if(c == 'l') {
        res.up = d.east;
        res.down = d.west;
        res.east = d.down;
        res.west = d.up;
        res.south = d.south;
        res.north = d.north;
    }
    
    else if(c == 'r') {
        res.up = d.west;
        res.down = d.east;
        res.east = d.up;
        res.west = d.down;
        res.south = d.south;
        res.north = d.north;
    }
    
    return res;
}

char next_dir(char c, int A, int B)
{
    // c : 현재 방향
    // A : 주사위 down 
    // B : map 숫자
    char nc;
    
    if(A > B) {
        switch(c) {
            case 'u' :
                nc = 'r';
                break;
            case 'd' :
                nc = 'l';
                break;
            case 'l' : 
                nc = 'u';
                break;
            case 'r' :
                nc = 'd';
                break;
            default : 
                break;
        }
    }
    
    else if(A < B) {
        switch(c) {
            case 'u' :
                nc = 'l';
                break;
            case 'd' :
                nc = 'r';
                break;
            case 'l' : 
                nc = 'd';
                break;
            case 'r' :
                nc = 'u';
                break;
            default : 
                break;
        }
    }
    
    else if(A == B) {
        nc = c;
    }
    
    return nc;
}

pair<char, pair<int, int>> next_pos(char c, pair<int, int> pos)
{
    // pos : 현재 주사위 위치 
    // c : 현재 방향 
    
    // 다음 방향 + 다음 위치  
    pair<char, pair<int, int>> res;
    
    if(c == 'u') {
        if(pos.first == 1) {
            res.first = 'd';
            res.second.first = 2;
            res.second.second = pos.second;
        }
        else {
            res.first = c;
            res.second.first = pos.first - 1;
            res.second.second = pos.second;
        }
    }
    
    else if(c == 'd') {
        if(pos.first == n) {
            res.first = 'u';
            res.second.first = n-1;
            res.second.second = pos.second;
        }
        else {
            res.first = c;
            res.second.first = pos.first + 1;
            res.second.second = pos.second;
        }
    }
    
    else if(c == 'l') {
        if(pos.second == 1) {
            res.first = 'r';
            res.second.first = pos.first;
            res.second.second = 2;
        }
        else {
            res.first = c;
            res.second.first = pos.first;
            res.second.second = pos.second - 1;
        }
    }
    
    else if(c == 'r') {
        if(pos.second == m) {
            res.first = 'l';
            res.second.first = pos.first;
            res.second.second = m-1;
        }
        else {
            res.first = c;
            res.second.first = pos.first;
            res.second.second = pos.second + 1;
        }
    }
    
    return res;
}

vector<pair<int, int>> bfs(int sy, int sx)
{
    queue<pair<int, int>> q;
    vector<pair<int, int>> v;
    
    int num = map[sy][sx];
    memset(visited, false, sizeof(visited));
    
    q.push({sy, sx});
    v.push_back({sy, sx});
    visited[sy][sx] = true;
    
    while(!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        
        for(int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            
            if(visited[ny][nx])
                continue;
                
            if(ny <= 0 || nx <= 0 || ny > n || nx > m)
                continue;
            
            if(num == map[ny][nx]) {
                q.push({ny, nx});
                v.push_back({ny, nx});
                visited[ny][nx] = true;
            }
        }
    }
    
    return v;
}

void calc_score()
{
    memset(visited, false, sizeof(visited));
    
    for(int sy = 1; sy <= n; sy++) {
        for(int sx = 1; sx <= m; sx++) {
            if(visited[sy][sx])
                continue;
            
            vector<pair<int, int>> v = bfs(sy, sx);
            
            int num = map[sy][sx];
            int size = v.size();
            int scr = num * size;
            
            for(auto p : v) {
                score[p.first][p.second] = scr;
                visited[p.first][p.second] = true;
            }
        }
    }
}

void game()
{
    // 처음에 동쪽(right)으로 이동
    char c = 'r';
    int A, B;
    pair<int, int> pos = {1, 1};
    
    while(k--) {
        // 주사위 위치
        pair<char, pair<int, int>> nPos = next_pos(c, pos);
        c = nPos.first;
        pos.first = nPos.second.first;
        pos.second = nPos.second.second;
        
        // 주사위 굴리기기
        dice = roll_dice(dice, c);
        
        // 주사위 밑면, 맵 숫자 구하기
        A = dice.down;
        B = map[pos.first][pos.second];
        
        // 결과 계산
        result += score[pos.first][pos.second];
        
        // 다음 방향 계산
        c = next_dir(c, A, B);
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    calc_score();
    game();
    
    cout << result;
}