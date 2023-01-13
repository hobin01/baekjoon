#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int fiboPositive[1000001];
int fiboNegative[1000001];
int n;
int mod = 1000000000;

void init()
{
  cin >> n;
  memset(fiboPositive, 0, sizeof(fiboPositive));
  memset(fiboNegative, 0, sizeof(fiboNegative));

  fiboPositive[0] = 0;
  fiboPositive[1] = 1;
  fiboPositive[2] = 1;

  fiboNegative[0] = 0;
  fiboNegative[1] = 1;
  fiboNegative[2] = -1;
}

int fibo(int num)
{
  int absN = abs(num);
  for(int i = 3; i <= absN; i++) {
    fiboPositive[i] = (fiboPositive[i - 1] + fiboPositive[i - 2]) % mod;
    fiboNegative[i] = (fiboNegative[i - 2] - fiboNegative[i - 1]) % mod;
  }

  if(num >= 0)
    return fiboPositive[num];
  else
    return fiboNegative[absN];
}

void printResult(int f)
{
  if(f > 0)
    cout << 1 << '\n';
  else if(f == 0)
    cout << 0 << '\n';
  else
    cout << -1 << '\n';

  cout << abs(f);
}

int main() {
  init();
  int f = fibo(n);
  printResult(f);
}