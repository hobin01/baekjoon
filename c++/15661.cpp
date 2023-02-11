#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 최대 판 400 칸
// 20C1 + 20C2 + ... + 20C20 = 2^20 - 1 
// 크게 잡아도 400 * 2^20 정도 브루트포스하면 나올지도???
// 그리고 값이 1 이상이니 혼자 팀하는 경우는 없음

int n;
int map[21][21];
vector<int> team1;
vector<int> team2;
int result;

void init()
{
  cin >> n;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      cin >> map[i][j];
    }
  }

  result = 987654321;
}

int calc(vector<int> &team)
{
  // team 1, 2 인 애들 값 구하기
  int res = 0;
  for(int i = 0; i < team.size(); i++) {
    for(int j = 0; j < team.size(); j++) {
      res += map[team[i]][team[j]];
    }
  }

  return res;
}

int main()
{
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  init();

  // team1 사람 수 2,3,4,...,10 명인 순으로 
  // 조합 구해서 브루트포스 
  vector<int> vec;
  for(int i = 1; i <= n; i++) {
    vec.push_back(i);
  }

  for(int i = 2; i <= (n / 2); i++) {
    vector<bool> chk(n, true);
    for(int j = 0; j < i; j++) {
      chk[j] = false;
    }

    do {
      team1.clear();
      team2.clear();
      for(int k = 0; k < n; k++) {
        if(chk[k] == false)
          team1.push_back(vec[k]);
        else
          team2.push_back(vec[k]);
      }

      int diff = abs(calc(team1) - calc(team2));
      result = min(result, diff);
    } while(next_permutation(chk.begin(), chk.end()));
  }

  cout << result;
}