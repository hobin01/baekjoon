#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;

int n;
int parent[1001]; // i번 직사각형의 부모

struct info {
  double x1;
  double y1;
  double x2;
  double y2;
};

vector<info>rect; // 직사각형

// 입력으로 들어온 애들 겹치는 지 여부 확인
// 겹치면 유니온 파인드로 부모 합치기
// 아니면 놔두기
// n^2 루프 돌면서 부모 합치고 마지막에 부모 개수 세면 분리된 애들 개수

void init()
{
  memset(parent, 0, sizeof(parent));
  
  cin >> n;

  rect.push_back({0,0,0,0});
  
  for(int i = 1; i <= n; i++) {
    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    info tmp = {x1, y1, x2, y2};
    rect.push_back(tmp);

    parent[i] = i;
  }
}

bool meet(int i, int j)
{
  // i, j 번 직사각형 만나는지 여부
  info info_i = rect[i];
  info info_j = rect[j];

  double x1 = info_i.x1;
  double x2 = info_i.x2;
  double y1 = info_i.y1;
  double y2 = info_i.y2;

  double x3 = info_j.x1;
  double x4 = info_j.x2;
  double y3 = info_j.y1;
  double y4 = info_j.y2;

  if(x1 < x3 && x4 < x2 && y1 < y3 && y4 < y2)
    return false;
  if(x1 > x3 && x4 > x2 && y1 > y3 && y4 > y2)
    return false;
  if(x3 > x2 || x4 < x1 || y3 > y2 || y4 < y1)
    return false;
  return true;
}


int find_parent(int idx)
{
  // idx 번 직사각형의 부모 찾기
  if(idx == parent[idx])
    return idx;
  else {
    parent[idx] = find_parent(parent[idx]);
    return parent[idx];
  }
}

void union_parent(int i, int j)
{
  // i, j번 직사각형 부모 합치기
  int parent_i = find_parent(i);
  int parent_j = find_parent(j);
  parent[parent_j] = parent_i;
}

int main() {
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  init();
  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j <= n; j++) {
      bool meet_chk = meet(i, j);
      if(meet_chk) {
        // 만나면 부모 합치기
        union_parent(i, j);
      }
    }
  }

  // 분리된 애들 체크용
  // 부모 다르면 분리된 것
  // 원점 부모는 제외 
  set<int> s;
  for(int i = 0; i <= n; i++) {
    int p = find_parent(i);
    s.insert(p);
  }
  
  cout << s.size() - 1;
}