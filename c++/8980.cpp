#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct box {
  int from;
  int to;
  int cap;
};

int N, C, M;
box boxes[10001]; // 박스 정보
int capacity[10001]; // 마을 별 도착했을 때 박스 양 
int result;

// 도착 기준 오름차순 후 시작 기준 오름차순 정렬
// 지나온 곳은 다시 안 가기 때문
// 시작부터 도착까지 최대한 많이 싣기

void init()
{
  cin >> N >> C >> M;
  for(int i = 0; i < M; i++) {
    int f, t, c;
    cin >> f >> t >> c;
    boxes[i] = {f, t, c};
    capacity[i] = 0;
  }

  result = 0;
}

bool cmp(const box &b1, const box &b2)
{
  // 오름차순 기준 : 도착, 출발 순
  if(b1.to < b2.to)
    return true;
  else if(b1.to == b2.to)
    return b1.from < b2.from;
  return false;
}

void calc()
{
  sort(boxes, boxes + M, cmp);
  
  for(int i = 0; i < M; i++) {
    int tmp = 0; // from ~ to 까지 싣을수 있는 최대 박스양
    int f = boxes[i].from;
    int t = boxes[i].to;
    int c = boxes[i].cap;

    for(int j = f; j < t; j++) {
      tmp = max(tmp, capacity[j]);
    }

    int left = min(c, C - tmp); // 싣을 수 있는 남은 양
    result += left;

    // 더 싣기
    for(int j = f; j < t; j++) {
      capacity[j] += left;
    }
  }

  cout << result;
}

int main() {
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  init();
  calc();
}