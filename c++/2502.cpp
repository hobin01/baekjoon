#include <iostream>

using namespace std;

// f1 = a, f2 = b
// fn = fibo * a + fibo * b
// 피보나치 수열 최대 30개니 그냥 미리 구하기
// 거기 맞는 거에다가 떡 최대 10만개니 브루트포스
int d, k;
int fibo1[31];
int fibo2[31];
int a, b; // 1,2번째 날 준 떡

void init()
{
  cin >> d >> k;

  fibo1[1] = 1;
  fibo2[1] = 0;
  fibo1[2] = 0;
  fibo2[2] = 1;
  
  fibo1[3] = 1;
  fibo2[3] = 1;
  fibo1[4] = 1;
  fibo2[4] = 2;

  for(int i = 5; i <= 30; i++) {
    fibo1[i] = fibo1[i - 1] + fibo1[i - 2];
    fibo2[i] = fibo2[i - 1] + fibo2[i - 2];
  }
}

void calc()
{
  // 답 아무거나 출력해도 됨
  int f1 = fibo1[d];
  int f2 = fibo2[d];
  
  for(int i = 1; i <= k; i++) {
    int rest = k - f1 * i;
    if(rest % f2 == 0) {
      a = i;
      b = (rest / f2);
      break;
    }
  }
}

int main() 
{
  init();
  calc();
  cout << a << '\n' << b;
}