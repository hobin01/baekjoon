#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int> vec; // 원래 입력된 수들로 만든 누적합 (% m)
vector<int> sum; // 누적 합 카운트 (0 ~ m-1)
long long result;

void init()
{
  cin >> n >> m;
  vec.push_back(0); // 맨 앞에 0 넣어두기 (첫 번째랑 구분용)
  sum.resize(m, 0);
  
  int num, prev;
  for(int i = 1; i <= n; i++) {
    cin >> num;
    prev = vec[i - 1];
    vec.push_back((prev + num) % m);
  }

  result = 0;
}

void getSum()
{
  for(auto v : vec) {
   sum[v]++;   
  }
}

long long nC2(long long num)
{
  // n * (n-1) / 2
  return (num * (num - 1)) >> 1;
}

void calc()
{
  for(auto s : sum) {
    if(s >= 2) {
      result += nC2((long long)(s));
    }
  }
}

int main() {
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  init();
  getSum();
  calc();

  cout << result;
}