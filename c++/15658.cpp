#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> nums;
int opers[4];
int res1;
int res2;

void init()
{
  cin >> n;
  nums.resize(n);
  for(int i = 0; i < n; i++) {
    cin >> nums[i];
  }
  for(int i = 0; i < 4; i++) {
    cin >> opers[i];
  }
  res1 = -1000000001; // 최대값
  res2 = 1000000001; // 최소값
}

void calc(int idx, int res)
{
  // idx : oper's index
  if(idx == n) {
    res1 = max(res1, res);
    res2 = min(res2, res);
    return;
  }

  for(int i = 0; i < 4; i++) {
    if(opers[i] > 0) {
      opers[i] -= 1;

      if(i == 0) {
        calc(idx + 1, res + nums[idx]);
      }
      else if(i == 1) {
        calc(idx + 1, res - nums[idx]);
      }
      else if(i == 2) {
        calc(idx + 1, res * nums[idx]);
      }
      else if(i == 3) {
        calc(idx + 1, res / nums[idx]);
      }

      opers[i] += 1;
    }
  }

  return;
}

int main() {
  init();

  calc(1, nums[0]);

  cout << res1 << '\n' << res2;
}