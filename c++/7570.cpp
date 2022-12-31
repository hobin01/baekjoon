#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int num[1000001];
int loc[1000001];
int dp[1000001];
int result;


// 가장 긴 부분 수열 (오름차순) 이면서 차이가 1씩만 나야 안 움직여진다. 그 애들을 최대로 하면 됨

void init()
{
  cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> num[i];
    loc[num[i]] = i;
    dp[i] = 1;
  }
  result = 0;
}

void calc()
{
  for(int i = 1; i <= n; i++) {
    int curNum = num[i];
    int curIdx = i;
    int prevNum = num[i] - 1;
    int prevIdx = loc[prevNum];

    if(curNum == 1)
      continue;

    if(curIdx > prevIdx) {
      dp[curNum] = dp[prevNum] + 1;
    }    
  }

  int tmp = 0;
  for(int i = 1; i <= n; i++) {
    tmp = max(tmp, dp[i]);
  }

  result = n - tmp;
  cout << result;
}

int main() {
  ios_base :: sync_with_stdio(false);  
  cin.tie(NULL);
  cout.tie(NULL);
  
  init();
  calc();
}