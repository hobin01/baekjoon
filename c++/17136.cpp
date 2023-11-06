#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

// 색종이 각 5개
// 색종이 좌상단 기준으로 붙힘
// 백트래킹 

int map[10][10];
bool visited[10][10]; // 방문여부
int paper[6] = {0, 5, 5, 5, 5, 5}; // 색종이 1 ~ 5 칸짜리 5개 
int res;

void init()
{
    memset(visited, false, sizeof(visited));
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            cin >> map[i][j];
            if(map[i][j] == 0) 
                visited[i][j] = true;
        }
    }
    res = 26; // 최대 25개 사용 가능 (실제로는 다 안 씀)
    return;
}

// 붙히는 거 가능한지 판단
bool possible(int y, int x, int d)
{
    // y,x : 현재 탐색 위치 
    // d : 길이 
    
    // 칸 넘어감
    if((y+d-1) >= 10 || (x+d-1) >= 10)
        return false;
    
    // 0인 거 있거나 이미 방문했음 
    for(int i = y; i < (y+d); i++) 
        for(int j = x; j < (x+d); j++) 
            if(visited[i][j]) 
                return false;
    
    // 가능 
    return true;
}

// 다음 탐색 위치 계산산
pair<int, int> next_pos(int y, int x) 
{
    // 끝 도달 
    if(y == 9 && x == 9) {
        return {-1, -1};
    }
    
    int ny = y;
    int nx = x+1;
    
    // 줄 바뀜 
    if(x == 9) {
        ny = y+1;
        nx = 0;
    }
    
    return {ny, nx};
}

// 색종이 붙히거나 뗌
void take_paper(int y, int x, int d, bool b)
{
    // y, x : 탐색 위치, d : 길이, b : true : 붙힘, false : 뗌
    for(int i = y; i < (y+d); i++) {
        for(int j = x; j < (x+d); j++) {
            visited[i][j] = b;
        }
    }
    
    if(b)
        paper[d]--;
    else 
        paper[d]++;
        
    return;
}

// 계산 : 백트래킹 
void calc(int y, int x, int cnt)
{
    // y,x : 현재 탐색 위치 
    // cnt : 현재까지 붙힌 개수 
    
    // 끝난 경우 
    if(y == -1 && x == -1) {
        res = min(res, cnt);
        return;
    }
    
    // 다음 칸 
    pair<int, int> npos = next_pos(y, x);
    int ny = npos.first;
    int nx = npos.second;
    
    // 붙혔거나 0인 경우 
    if(visited[y][x]) {
        calc(ny, nx, cnt);
        return;
    }
    
    // 색종이 붙히기
    for(int d = 1; d <= 5; d++) {
        
        // 가능한 경우 
        bool can_put = possible(y, x, d);
        
        // 아직 남음
        if(paper[d] > 0) {
            // 붙힐 수 있음 
            if(can_put) {
                // 붙힘
                take_paper(y, x, d, true);
                
                calc(ny, nx, cnt+1);
                
                // 다음 거 해보기 위해서 뗌
                take_paper(y, x, d, false);
            }
        }
        
        // 안 남건, 남아있건 못 붙히면 더 큰 것도 못 붙힘 
        if(can_put == false) {
            break;
        }
    }
    
    return;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    calc(0, 0, 0);
    if(res == 26) {
        cout << -1;
    } 
    else {
        cout << res;
    }
    return 0;
}