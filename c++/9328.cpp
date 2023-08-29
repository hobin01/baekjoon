#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <string>

using namespace std;

int T, h, w;
char map[102][102];
bool keys[26];
bool visited[102][102];

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1}; // 상하좌우

void init()
{
    memset(map, 0, sizeof(map));
    memset(keys, 0, sizeof(keys));
    memset(visited, 0, sizeof(visited));
    
    cin >> h >> w;
    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            cin >> map[i][j];
        }
    }
    
    string s;
    cin >> s;
    if(s[0] == '0')
        return;
    else {
        for(auto c : s) {
            keys[c - 'a'] = true;
        }
    }
    return;
}

void calc()
{
    int res = 0;
    
    queue<pair<int, int>> q;
    queue<pair<int, int>> door[26]; // 잠긴 문 
    
    q.push({0, 0});
    visited[0][0] = true;
    
    while(!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        
        for(int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            
            // 범위 밖
            if(nx < 0 || nx > (w+1) || ny < 0 || ny > (h+1))
                continue;
            
            // 벽인 경우 
            else if(map[ny][nx] == '*')
                continue;
            
            // 이미 왔던 경우 
            else if(visited[ny][nx])
                continue;
                
            visited[ny][nx] = true;
            
            // 문인 경우 
            if(map[ny][nx] >= 'A' && map[ny][nx] <= 'Z') {
                // 열쇠 있는 경우 
                if(keys[map[ny][nx] - 'A']) {
                    q.push({ny, nx});
                }
                // 없는 경우 
                // 새로 열릴 수 있음
                else {
                    door[map[ny][nx] - 'A'].push({ny, nx});
                }
            }
            // 열쇠인 경우 
            else if(map[ny][nx] >= 'a' && map[ny][nx] <= 'z') {
                q.push({ny, nx});
                keys[map[ny][nx] - 'a'] = true;
                
                // 새로 열어 보기 
                while(!door[map[ny][nx] - 'a'].empty()) {
                    pair<int, int> pos = door[map[ny][nx] - 'a'].front();
                    q.push(pos);
                    door[map[ny][nx] - 'a'].pop();
                }
            }
            
            // 길 또는 돈 
            else {
                q.push({ny, nx});
                if(map[ny][nx] == '$')
                    res++;
            }
        }
    }
    
    cout << res << '\n';
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> T;
    while(T--) {
        init();
        calc();
    }
}