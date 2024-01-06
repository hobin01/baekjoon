#include <iostream>
using namespace std;

int main()
{
    int n,k;
    cin >> n >> k;
    // 메모리 아주 작으니 loop로 변경
    // f(0,k) = 0, f(n,k) = (f(n-1,k) + k -1 mod n) + 1
    int f = 0;
    for(int i = 1; i <= n; i++) {
        f = (f+k-1) % i + 1;
    }
    cout << f;
}