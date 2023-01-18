#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// 문자열 뒤에 A추가
// 문자열 뒤에 B추가 + 문자열 reverse
// 주어진 문자열 S, 바꿀 문자열 T
// 가능하면 1, 아니면 0

string S, T;
bool result;
int sSize;

void init()
{
  cin >> S >> T;
  result = false;
  sSize = S.size();
}

void dfs(string t)
{
  if(result)
    return;

  if(t == S) {
    result = true;
    return;
  }

  int tSize = t.size();
  if(tSize <= sSize)
    return;

  if(t[tSize - 1] == 'A') {
    string t1 = t.substr(0, tSize - 1);
    dfs(t1);
  }

  if(t[0] == 'B') {
    reverse(t.begin(), t.end());
    string t2 = t.substr(0, tSize - 1);
    dfs(t2);
  }

  return;
}

int main() {
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  init();

  dfs(T);
  cout << result;
}