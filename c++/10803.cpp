#include <iostream>

using namespace std;

int n, m;
int dp[10001][101] = {0, }; // 최대값 100만
int inf = 987654321;

void init() {
    cin >> n >> m;
}

int calc(int x, int y) {
    if(x % y == 0) return x / y;
    if(x == y) return 1;

    int &v = dp[x][y];
    if(v != 0) return v;

    if(x >= 3 * y) {
        v = x * y;
        v = min(v, calc(x - y, y) + 1);
        return v;
    }

    int a, b; 
    v = inf;
    for(int i = 1; i <= (x/2); i++) {
        a = calc(i, y);
        b = calc(x - i, y);
        v = min(v, a + b);
    }
    for(int j = 1; j <= (y/2); j++) {
        a = calc(x, j);
        b = calc(x, y - j);
        v = min(v, a + b);
    }

    return v;
}

int main() {
    init();
    if(n < m) swap(n, m);
    cout << calc(n, m);
}
