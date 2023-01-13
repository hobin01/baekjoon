#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 0부터 시작
// 웅덩이 1,6 => 1,2,3,4,5 를 덮어야 함
// 웅덩이 처음부터 일단 덮어감
// 그리고 널판지 마지막이 웅덩이면 그냥 이어서
// 아니면 그 다음 웅덩이 시작부터
// 이러면 최소로 항상 나올 듯??
// 겹치는 입력 있을 수도 있으니 처리해주기
// 정렬 시킨 다음에 vec에 있는 애들 보면서
// 겹쳐지면 end 부분을 max 로 업데이트
// 안 겹치면 새로 push

int N, L;
vector<pair<int,int>> vec;
vector<pair<int,int>> holes;
int result;

void init()
{
  cin >> N >> L;
  for(int i = 0; i < N; i++) {
    int s, e;
    cin >> s >> e;
    vec.push_back({s, e - 1});
  }

  result = 0;

  // 일단 시작, 끝 점 오름차순 정렬
  sort(vec.begin(), vec.end());
}

void makeHoles()
{
  holes.push_back(vec[0]);

  for(int i = 1; i < N; i++) {
    pair<int,int> new_p = vec[i];
    pair<int,int> prev_p = holes[holes.size() - 1];
    // 포함되는 경우
    if(new_p.second <= prev_p.second) {
      continue;    
    }

    // 겹치는 경우
    else if(new_p.first >= prev_p.first && new_p.first <= prev_p.second && new_p.second >= prev_p.second) {
      prev_p.second = new_p.second;
      holes[holes.size() - 1] = prev_p;
    }

    // 안 겹치는 경우
    else if(new_p.first > prev_p.second) {
      holes.push_back(new_p);
    }
  }
}

void calc()
{
  int s = holes[0].first;
  int e = 0;
  int cur = 0;
  int h_size = holes.size();
  
  for(int i = 0; i < h_size; i = cur) {
    
    e = s + L - 1;
    result++;
    
    // 아직 i번 구멍 안 끝남
    if(e < holes[i].second) {
      s = e + 1;
      cur = i;
    }

    // i번 구멍 끝
    else if(e >= holes[i].second) {
      // 다음 구멍 없음
      if(e >= holes[h_size - 1].second)
        return;

      // e 가 위치한 구멍 몇 번째인지 구하기
      for(int j = i; j < h_size; j++) {
        // j 번 중간에 있음
        if(holes[j].first <= e && e < holes[j].second) {
          s = e + 1;
          cur = j;
        }
        // j번 끝에 있음
        else if(e == holes[j].second) {
          s = holes[j + 1].first;
          cur = j + 1;
        }
        // 애매한 곳에 있음
        else if(holes[j].second < e && e < holes[j + 1].first) {
          s = holes[j + 1].first;
          cur = j + 1;          
        }
      }
    }
  }
}

int main() {
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  init();
  makeHoles();
  calc();

  cout << result;
}