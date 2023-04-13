#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// 피보나치 수열 합 S(n) = F(n+2) - 1
// F(1)=F(2)=1
// 피보나치 수열 행렬 표현
// (F(n+1), F(n)) = ((1 1) (1 0))^n * (1 0)

long long mod = 1000000000;

string binary(long long n) {
  // bin(n)
  string bin = "";
  while(n > 0) {
    bin += (n & 1) + '0';
    n >>= 1;
  }
  reverse(bin.begin(), bin.end());
  return bin;
}

pair<pair<long long, long long>, pair<long long, long long>> mul(pair<pair<long long, long long>, pair<long long, long long>>A, pair<pair<long long, long long>, pair<long long, long long>>B) {
  // A*B
  // mat : ((x11 x12) (x21 x22))
  pair<pair<long long, long long>, pair<long long, long long>> res = {{0, 0}, {0, 0}};

  res.first.first = (A.first.first * B.first.first + A.first.second * B.second.first) % mod;
  res.first.second = (A.first.first * B.first.second + A.first.second * B.second.second) % mod;
  res.second.first = (A.second.first * B.first.first + A.second.second * B.second.first) % mod;
  res.second.second = (A.second.first * B.first.second + A.second.second * B.second.second) % mod;
  return res;
}

pair<long long, long long> power(long long p) {
  string bin_p = binary(p);

  pair<pair<long long, long long>, pair<long long, long long>> mat = {{1, 1}, {1, 0}};
  pair<pair<long long, long long>, pair<long long, long long>> baseMat = {{1, 1}, {1, 0}};
  
  for(int i = 1; i < bin_p.size(); i++) {
    // 제곱 후 곱셈
    mat = mul(mat, mat);
    if(bin_p[i] == '1') {
      mat = mul(mat, baseMat);
    }
  }

  // (1, 0) 곱하기
  pair<long long, long long> res = {0, 0};
  res.first = mat.first.first;
  res.second = mat.second.first;
  return res;
}

long long sum(long long n) {
  // F(1) ~ F(n) 까지 합 = S(n) = F(n+2) - 1
  long long pow = n + 1;

  pair<long long, long long> mat = power(pow);
  long long Sn = mat.first - 1LL;
  return Sn;
}

int main() {
  long long a, b;
  cin >> a >> b;
  if(a == 1LL) {
    cout << sum(b);
    return 0;
  }
  
  long long Sa = sum(a - 1);
  long long Sb = sum(b);
  long long res = Sb - Sa;
  if(res < 0) {
    res += mod;
  }
  cout << res;
}