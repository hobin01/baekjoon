#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long n;
int k, q;
long long x, y;

void init()
{
	cin >> n >> k >> q;
}

void get_num()
{
	cin >> x >> y;
}

// num의 부모는 (num - 2) / k + 1
long long get_parent(long long num)
{
	return (num - 2) / k + 1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	if (k == 1) {
		while (q--) {
			get_num();
			cout << ((x > y) ? (x - y) : (y - x)) << '\n';
		}
	}

	else {
		while (q--) {
			get_num();

			int cnt = 0;

			while (true) {
				// 같은 수 나오면 종료 (LCA)
				if (x == y)
					break;

				// 더 깊이 있는 수 기준으로 부모 찾아 올라가기
				if (x > y) {
					x = get_parent(x);
				}
				else {
					y = get_parent(y);
				}

				cnt++;
			}

			cout << cnt << '\n';
		}
	}
}