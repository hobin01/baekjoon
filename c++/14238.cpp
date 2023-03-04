#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;
// 규칙 : A는 아무데나 와도 됨, BB 는 안 됨, CCA, CCB, CCC, CAC, CBC 는 안 됨

string str;
string res;
int cnt[4];
bool dp[51][51][51][4][4];
// dp[a][b][c][b1][b2] : a, b, c 만큼 썼고, b1, b2 는 하루 전, 이틀 전 쓴 거
// 끝까지 다 썼는데 다 통과하면 그게 정답

void init()
{
  cin >> str;
  for(auto c : str) {
    if(c == 'A')
      cnt[1]++;
    else if(c == 'B')
      cnt[2]++;
    else if(c== 'C')
      cnt[3]++;
  }
  memset(dp, false, sizeof(dp));
  res.resize(str.size());
}

bool calc(int a, int b, int c, int b1, int b2)
{
  // 다 씀
  if(a == cnt[1] && b == cnt[2] && c == cnt[3])
    return true;

  // 이미 계산된 경우
  if(dp[a][b][c][b1][b2])
    return false;

  dp[a][b][c][b1][b2] = true;

  // A 가능
  if(a + 1 <= cnt[1]) {
    res[a + b + c] = 'A';
    bool chk = calc(a + 1, b, c, 1, b1);
    if(chk)
      return true;
  }

  // B 가능
  if(b + 1 <= cnt[2]) {
    res[a + b + c] = 'B';
    if(b1 != 2) {
      bool chk = calc(a, b + 1, c, 2, b1);
      if(chk)
        return true;
    }
  }

  // C 가능
  if(c + 1 <= cnt[3]) {
    res[a + b + c] = 'C';
    if(b2 != 3 && b1 != 3) {
      bool chk = calc(a, b, c + 1, 3, b1);
      if(chk)
        return true;
    }
  }

  // 다 안 됨
  return false;
}

int main()
{
  init();
  bool chk = calc(0, 0, 0, 0, 0);
  if(chk)
    cout << res;
  else
    cout << -1;
}