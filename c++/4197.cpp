#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

#define INF 987654321

int r, c;
vector<pair<int, int>> fires;
pair<int, int> ji;
char map[1001][1001];
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };
int personDist[1001][1001]; // 지훈이로부터의 거리, 벽은 -1로
int fireDist[1001][1001]; // 불로부터의 거리, 벽은 -1로

void init()
{
    cin >> r >> c;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> map[i][j];
            personDist[i][j] = INF;
            fireDist[i][j] = INF;
            if (map[i][j] == 'J') {
                ji = { i, j };
                personDist[i][j] = 0;
            }
            else if (map[i][j] == 'F') {
                fires.push_back({ i,j });
                fireDist[i][j] = 0;
            }
            else if (map[i][j] == '#') {
                personDist[i][j] = -1;
                fireDist[i][j] = -1;
            }
        }
    }
}

void fail()
{
    cout << "IMPOSSIBLE";
}

// F와 J로부터 각 .까지 최단 거리를 미리 구함
// J의 값이 더 작으면서 가장 작은 값이 정답
// 없으면 탈출 불가

void bfs_person()
{
    // 지훈이로부터의 거리
    queue<pair<pair<int, int>, int>>q; // {위치, 거리}
    q.push({ ji,0 });
    bool visited[1001][1001];
    memset(visited, false, sizeof(visited));
    visited[ji.first][ji.second] = true;

    while (!q.empty()) {
        pair<int, int> person = q.front().first;
        int y = person.first;
        int x = person.second;
        int dist = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (ny < 0 || ny >= r || nx < 0 || nx >= c)
                continue;
            if (map[ny][nx] == '#' || map[ny][nx] == 'F')
                continue;
            if (visited[ny][nx] == true)
                continue;

            if (personDist[ny][nx] > dist + 1) {
                personDist[ny][nx] = dist + 1;
                visited[ny][nx] = true;
                q.push({ {ny, nx}, dist + 1 });
            }
        }
    }
}

void bfs_fires()
{
    // 불로부터의 거리

    for (auto f : fires) {
        queue<pair<pair<int, int>, int>>q;
        q.push({ f, 0 });
        bool visited[1001][1001];
        memset(visited, false, sizeof(visited));
        visited[f.first][f.second] = true;

        while (!q.empty()) {
            pair<int, int> fire = q.front().first;
            int y = fire.first;
            int x = fire.second;
            int dist = q.front().second;
            q.pop();

            for (int i = 0; i < 4; i++) {
                int ny = y + dy[i];
                int nx = x + dx[i];

                if (ny < 0 || ny >= r || nx < 0 || nx >= c)
                    continue;
                if (map[ny][nx] == '#' || map[ny][nx] == 'F')
                    continue;
                if (visited[ny][nx] == true)
                    continue;

                if (fireDist[ny][nx] > dist + 1) {
                    fireDist[ny][nx] = dist + 1;
                    visited[ny][nx] = true;
                    q.push({ {ny, nx}, dist + 1 });
                }
            }
        }
    }
}

int escape()
{
    int res = INF;
    for (int i = 0; i < c; i++) {
        if (personDist[0][i] < fireDist[0][i]) {
            res = min(res, personDist[0][i]);
        }
        if (personDist[r - 1][i] < fireDist[r - 1][i]) {
            res = min(res, personDist[r - 1][i]);
        }
    }
    for (int i = 0; i < r; i++) {
        if (personDist[i][0] < fireDist[i][0]) {
            res = min(res, personDist[i][0]);
        }
        if (personDist[i][c - 1] < fireDist[i][c - 1]) {
            res = min(res, personDist[i][c - 1]);
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();
    
    bfs_person();
    bfs_fires();

    int res = escape();

    if (res == INF) {
        fail();
    }
    else
        cout << res + 1; // 나가는 거 한 칸 추가
}