#include <iostream>
#include <set>

using namespace std;

int n, m, k;
// n : 격자 수, m : 상어 수, k : 냄새 수 
// 1,2,3,4 : 상하좌우 

struct info {
    int shark; // 상어 번호 (빈칸 : 0)
    int dir; // 상어 방향 (빈칸 : 0)
    int smell; // 냄새 남은 수 (빈칸 : 0)
};

// 아래 3개는 계속 갱신해야 함
pair<int, int> sharks[401]; // 현재 상어 위치
set<int> remains; // 남은 상어 목록 
info map[21][21]; // 전체 맵 

int prior[401][5][4]; // 상어 별 방향 우선순위 
// [i][j][k] : i 번 상어 j 방향일 때 k 번 우선순위 

int dy[5] = {0, -1, 1, 0, 0};
int dx[5] = {0, 0, 0, -1, 1}; // 상하좌우 1234

int result; // 정답 

void init()
{
    cin >> n >> m >> k;
    
    int s; // 상어 번호 
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> s;
            if(s != 0) {
                sharks[s] = {i, j};
                remains.insert(s);
            }
            map[i][j] = {0, 0, 0};
        }
    }
    
    int x, y, curDir; // 상어 위치, 방향 
    for(s = 1; s <= m; s++) {
        cin >> curDir;
        y = sharks[s].first;
        x = sharks[s].second;
        map[y][x] = {s, curDir, k};
    }
    
    int zero, one, two, three; // 우선순위 값들
    for(s = 1; s <= m; s++) {
        for(int i = 1; i <= 4; i++) {
            cin >> zero >> one >> two >> three;
            prior[s][i][0] = zero;
            prior[s][i][1] = one;
            prior[s][i][2] = two;
            prior[s][i][3] = three;
        }
    }
    
    result = 0;
}

int new_dir_shark(int num)
{
    // num : 상어 번호 
    // return : 새 이동 방향 
    int res = 0;
    
    // 현재 상어 위치, 방향 
    int y = sharks[num].first;
    int x = sharks[num].second;
    int dir = map[y][x].dir;
    
    // 빈 칸 중 이동 가능한 칸들 
    for(int i = 0; i < 4; i++) {
        int p = prior[num][dir][i];
        int ny = y + dy[p];
        int nx = x + dx[p];
        
        if(ny <= 0 || ny > n || nx <= 0 || nx > n)
            continue;
            
        if(map[ny][nx].shark == 0) {
            res = p;
            break;
        }
    }
    
    if(res != 0)
        return res;
        
    // 빈 칸 없어 자신의 냄새 방향으로 
    for(int i = 0; i < 4; i++) {
        int p = prior[num][dir][i];
        int ny = y + dy[p];
        int nx = x + dx[p];
        
        if(ny <= 0 || ny > n || nx <= 0 || nx > n)
            continue;
            
        if(map[ny][nx].shark == num) {
            res = p;
            break;
        }
    }
    
    return res;
}

void move_sharks()
{
    int new_dir[401]; // 상어 새 방향 
    
    // 상어 이동 방향 결정 
    for(auto s : remains) {
        new_dir[s] = new_dir_shark(s);
    }
    
    set<int> outSharks; // 쫓겨날 애들 목록 
    
    // 상어 이동 
    // 이동했는데 누군가 있으면 번호 작은 애로 갱신 
    for(auto s : remains) {
        int nd = new_dir[s];
        int ny = sharks[s].first + dy[nd];
        int nx = sharks[s].second + dx[nd];
        
        if(map[ny][nx].shark == 0) {
            // 빈 칸인 경우 
            sharks[s] = {ny, nx};
            map[ny][nx] = {s, nd, k+1}; // 이후에 한 번에 갱신 위해 +1
        }
        else if(map[ny][nx].shark == s) {
            // 자기 냄새인 경우 
            sharks[s] = {ny, nx};
            map[ny][nx] = {s, nd, k+1};
        }
        else {
            // 이동했는데 쫓아냄
            if(map[ny][nx].shark > s) {
                sharks[s] = {ny, nx};
                map[ny][nx] = {s, nd, k+1};
                outSharks.insert(map[ny][nx].shark);
            }
            // 쫓겨남 
            else {
                outSharks.insert(s);
            }
        }
    }
    
    // 쫓겨날 애들 정리 
    for(auto s : outSharks) {
        remains.erase(s);
    }
}

void update_smell()
{
    // 냄새 업데이트 
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(map[i][j].smell > 1) {
                map[i][j].smell -= 1;
            }
            else if(map[i][j].smell == 1) {
                map[i][j] = {0, 0, 0};
            }
        }
    }
}

bool over()
{
    // 게임 끝 
    if(result > 1000) {
        result = -1;
        return true;
    }
    // 종료 여부 
    if(remains.size() == 1) {
        return true;
    }
    
    return false;
}

void game()
{
    while(true) {
        if(over()) {
            cout << result; 
            break;
        }
        
        move_sharks();
        update_smell();
        result++;
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    game();
}