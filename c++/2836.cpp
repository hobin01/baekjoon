#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
long long M;
long long result;
vector<pair<long long, long long>> people;

// 원래 방향대로 가는 사람은 가는 길에 태워다 주면 됨
// 역방향 이동하는 애들만 대상으로 선분 길이 구하는 
// 스위핑 동일하게 적용해서 * 2 하면 됨 (역방향이므로)

void init()
{
  cin >> N >> M;
  result += M; // 원래 가야하는 길이
  for(int i = 0; i < N; i++) {
    long long from, to;
    cin >> from >> to;
    if(from < to)
      continue;
    people.push_back({to, from});
  }

  sort(people.begin(), people.end());
}

void calc()
{
  // 스위핑으로 선분 길이 구하는 거랑 동일 (*2 만 차이)
  long long start = -1;
  long long last = -1;

  for(auto p : people) {
    // 선분 끊어짐
    if(last < p.first) {
      result += (last - start) * 2;
      start = p.first;
    }
    // 선분 갱신
    if(last < p.second) {
      last = p.second;
    }
  }

  result += (last - start) * 2;
  cout << result;
}

int main() {
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  init();
  calc();
}