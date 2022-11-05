#include <iostream>
using namespace std;
void calc(int sub)
{
  if(sub == 0) {
    cout << 0 << '\n';
    return;
  }
  else if(sub == 1 || sub == 2) {
    cout << sub << '\n';
    return;
  }
  else {
    int cnt = 0;
    while(cnt * cnt < sub) {
      cnt++;
    }

    if(cnt * (cnt - 1) < sub) {
      cout << 2 * cnt - 1 << '\n';
    }
    else {
      cout << 2 * cnt - 2 << '\n';
    }
  }
}

int main() {
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  int n;
  int x, y;
  cin >> n;
  while(n--) {
    cin >> x >> y;
    int sub = y - x;
    calc(sub);
  }
}