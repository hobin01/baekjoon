#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;
// 톱니 N, S : 0, 1
// 회전 시계, 반시계 : 1, -1
// 같은 극이면 가만히, 다른 극이면 반대방향 회전
// (따라 가는 방향)
// 회전 영향 주는 거는 2, 6번쨰 값

int T, K;
// T : 톱니 개수, K : 회전 횟수
vector<vector<int>> wheels;
vector<pair<int, int>> rots;
vector<int> wheel_rot; // 바퀴 도는 방향

void init()
{
  cin >> T;
  string s;
  wheels.resize(T);
  for(int i = 0; i < T; i++) {
    cin >> s;
    for(auto c : s) {
      wheels[i].push_back(c - '0');
    }
  }

  cin >> K;
  int num, rot;
  for(int i = 0; i < K; i++) {
    cin >> num >> rot;
    rots.push_back({num - 1, rot});
  }
}

void rotation(int num, int rot)
{
  // num : num번쨰 톱니
  // rot : 회전 방향 : 1, -1, 시계, 반시계, 0 : 가만히

  vector<int> tmp(8);
  if(rot == 1) {
    // 시계 방향
    for(int i = 0; i < 7; i++) {
      tmp[i + 1] = wheels[num][i];
    }
    tmp[0] = wheels[num][7];
    wheels[num] = tmp;
  }
  else if(rot == -1) {
    // 반시계 방향
    for(int i = 1; i < 8; i++) {
      tmp[i - 1] = wheels[num][i];
    }
    tmp[7] = wheels[num][0];
    wheels[num] = tmp;
  }
}

void wheel_rot_clear()
{
  wheel_rot.clear();
  wheel_rot.resize(T, 0);
}

void calc_right(int num, int rot)
{
  // num번째 바퀴 rot로 회전시킬 때 바퀴들이 돌 방향 결정 (오른쪽 바퀴들)
  wheel_rot[num] = rot;

  // 끝
  if(num == T - 1)
    return;

  int p1 = wheels[num][2];
  int p2 = wheels[num + 1][6];

  // 더 이상 회전 X
  if(p1 == p2)
    return;

  else {
    if(rot == 1)
      calc_right(num + 1, -1);
    else if(rot == -1)
      calc_right(num + 1, 1);
  }
}

void calc_left(int num, int rot)
{
  // num번째 바퀴 rot로 회전시킬 때 바퀴들이 돌 방향 결정 (오른쪽 바퀴들)
  wheel_rot[num] = rot;

  // 끝
  if(num == 0)
    return;

  int p1 = wheels[num][6];
  int p2 = wheels[num - 1][2];

  // 더 이상 회전 X
  if(p1 == p2)
    return;

  else {
    if(rot == 1)
      calc_left(num - 1, -1);
    else if(rot == -1)
      calc_left(num - 1, 1);
  }
}

void calc()
{
  for(auto r : rots) {
    int num = r.first;
    int rot = r.second;

    wheel_rot_clear();
    calc_right(num, rot);
    calc_left(num, rot);

    for(int i = 0; i < T; i++) {
      rotation(i, wheel_rot[i]);
    }
  }

  // 12시 방향이 S 인 거 구하기
  int res = 0;
  for(int i = 0; i < T; i++) {
    if(wheels[i][0] == 1)
      res++;
  }

  cout << res;
}

int main()
{
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  init();
  calc();
}