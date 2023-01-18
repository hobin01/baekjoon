#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include <queue>

using namespace std;

// 칸 : n x m
// 배양액 : g, r
// 황토색 칸에만 뿌릴 수 있음 (2)
// 흰 칸에는 못 뿌림 (1)
// 1초 당 인접칸으로 퍼져나감
// 호수에는 안 퍼짐 (0)
// 원래 배양액 있는 곳으로도 안 퍼짐
// g, r 동시에 만나는 지점에 꽃 핌
// g, r개 배양액은 모두 써야 함
// 최대 꽃 개수는?

// 칸 최대 2500개
// 배양액 최대 10개
// g, r 최대 5개
// 배양액 위치 : 10!/5!5! = 252
// 각 케이스마다 브루트포스해도 얼추 10만번 정도

int n, m, g, r;
int land[51][51];
pair<int,int> yellow[11]; // 황색 땅 번호, 위치
map<string, bool> checkMap;
// 황색 땅 위치에 뿌렸었는지 체크용 (string은 sort한 상태로 넣기)
// 최대 10개이므로 0123456789 와 같이 넣기
int flower; // 꽃 개수

int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};
int cnt = 0; // yellow 칸 개수 

void init()
{
  cin >> n >> m >> g >> r;
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      cin >> land[i][j];
      if(land[i][j] == 2) {
        yellow[cnt] = {i, j};
        cnt++;
      }
    }
  }
  flower = -1;
}

int bfs(string green, string red)
{
  int res = 0; // 꽃 개수 
  // green : 0123, red : 5678
  // 0,1,2,3번 yellow 땅에 g
  // 5,6,7,8번 yellow 땅에 r 넣는 경우

  pair<int,char> check[51][51];
  // {시간, 색}
  // 색 : g, r, f
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      check[i][j] = {-1, 'b'}; // blank
    }
  }
  
  queue<pair<int,int>> q;

  for(int i = 0; i < green.size(); i++) {
    pair<int,int> gg = yellow[green[i] - '0'];
    q.push(gg);
    check[gg.first][gg.second] = {0, 'g'};
  }
  for(int i = 0; i < red.size(); i++) {
    pair<int,int> rr = yellow[red[i] - '0'];
    q.push(rr);
    check[rr.first][rr.second] = {0, 'r'};
  }

  while(!q.empty()) {
    pair<int,int> loc = q.front();
    q.pop();

    int t = check[loc.first][loc.second].first;
    char c = check[loc.first][loc.second].second;
    
    // 꽃인 경우
    if(c == 'f')
      continue;

    for(int i = 0; i < 4; i++) {
      int ny = loc.first + dy[i];
      int nx = loc.second + dx[i];

      // 벗어남
      if(ny < 0 || nx < 0 || ny >= n || nx >= m)
        continue;
      // 호수인 경우
      if(land[ny][nx] == 0)
        continue;

      int nt = t + 1;
      char nc = check[ny][nx].second;
      // 빈 칸인 경우
      if(nc == 'b') {
        check[ny][nx] = {nt, c};
        q.push({ny, nx});
      }
      else {
        // 배양액 만나는 경우
        if(nt == check[ny][nx].first && nc != c) {
          check[ny][nx] = {-1, 'f'};
          res++;
        }
        // 배양액 있는 경우
        else {
          continue;
        }
      }
    }
  }

  return res;
}

void calc()
{
  string gstr = "";
  string rstr = "";
  string str = "";
  for(int i = 0; i < cnt; i++) {
    str += char(i + '0');
  }

  do {
    gstr = str.substr(0, g);
    rstr = str.substr(g, r);

    sort(gstr.begin(), gstr.end());
    sort(rstr.begin(), rstr.end());
    
    string tmp = gstr + rstr;
    // 처음 탐색하는 값
    if(checkMap.find(tmp) == checkMap.end()) {
      checkMap.insert({tmp, true});
      flower = max(flower, bfs(gstr, rstr));
    }
    
  } while(next_permutation(str.begin(), str.end()));

  cout << flower;
}

int main() {
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  init();
  calc();
}