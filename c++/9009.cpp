#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> fibo;
vector<int> nums;

void init()
{
  cin >> n;
  while(n--) {
    int num;
    cin >> num;
    nums.push_back(num);
  }
}

void calc_fibo() 
{
  fibo.push_back(0);
  fibo.push_back(1);

  int idx = 1;
  while(fibo[idx] + fibo[idx - 1] <= 1000000000) {
    fibo.push_back(fibo[idx] + fibo[idx - 1]);
    idx++;
  }
}

void get_answer(int num)
{
  vector<int> answer;
  int idx = fibo.size() - 1;

  if(num >= fibo[idx]) {
    num -= fibo[idx];
    answer.push_back(fibo[idx]);
  }
  
  while(num != 0) {
    for(int i = idx; i >= 1; i--) {
      if(fibo[i] > num && num >= fibo[i - 1]) {
        num -= fibo[i - 1];
        answer.push_back(fibo[i - 1]);
        idx = i;
        break;
      }
    }
  }

  for(int i = answer.size() - 1; i >= 0; i--) {
    cout << answer[i] << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  init();
  calc_fibo();
  for(auto num : nums) {
    get_answer(num);
  }
}