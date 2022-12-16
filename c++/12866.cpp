#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int A, B, C;
bool check[1001][1001];
bool result;

void init()
{
  cin >> A >> B >> C;
  memset(check, false, sizeof(check));
  result = 0;
}

void bfs()
{
  // [min][max] 값 가질 때 가능한지 체크
  // 합 동일하므로 min, max 같으면 같은 경우
  // true 값 가지면 체크된 케이스이므로
  // 더 이상 탐색 안 해도 됨
  // bfs로 가능한 케이스 탐색
  // 오름차순 가정하고 탐색
  // A = B = C = (A+B+C) / 3 이면 탐색 종료
  // A + B + C 3의 배수 아니면 어짜피 안 됨
  if((A+B+C) % 3 != 0)
    return;

  // 합 : D
  int sum = A + B + C;
  int tmp = 0; // 임시값
  
  int m = min(min(A, B), C);
  int M = max(max(A, B), C);
  check[m][M] = true;

  queue<pair<int,int>> q;
  q.push({m, M});

  while(!q.empty()) {
    pair<int,int> p = q.front();
    q.pop();

    // m <= tmp <= M 순 되도록 큐에 들어있음
    m = p.first;
    M = p.second;
    tmp = sum - (m + M);

    // 최대 최소 같으면 다 같음
    if(m == M) {
      result = 1;
      break;
    }

    // m <- m + m
    // tmp <- tmp - m
    int arr[3];
    arr[0] = m + m;
    arr[1] = tmp - m;
    arr[2] = M;
    sort(arr, arr + 3);

    int mm = arr[0];
    int MM = arr[2];
    if(!check[mm][MM]) {
      check[mm][MM] = true;
      q.push({mm, MM});
    }

    // m <- m + m
    // M <- M - m
    arr[0] = m + m;
    arr[1] = tmp;
    arr[2] = M - m;
    sort(arr, arr + 3);

    mm = arr[0];
    MM = arr[2];
    if(!check[mm][MM]) {
      check[mm][MM] = true;
      q.push({mm, MM});
    }

    // tmp <- tmp + tmp
    // M <- M - tmp
    arr[0] = m;
    arr[1] = tmp + tmp;
    arr[2] = M - tmp;
    sort(arr, arr + 3);

    mm = arr[0];
    MM = arr[2];
    if(!check[mm][MM]) {
      check[mm][MM] = true;
      q.push({mm, MM});
    }
  }
}

int main() {
  init();
  bfs();
  cout << result;
}