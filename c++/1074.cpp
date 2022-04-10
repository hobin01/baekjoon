#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

int n, r, c;
int order[2][2] = { {0,1},{2,3} };

int func(int n, int r, int c, int first)
{
	if (n == 1)
		return first + order[r][c];

	int half = pow(2, n - 1);
	int last = pow(2, n);
	int diff = half * half;

	if (r >= 0 && r < half) {
		if (c >= 0 && c < half) {
			return func(n - 1, r, c, first);
		}
		else if (c >= half && c < last) {
			return func(n - 1, r, c - half, first + diff);
		}
	}
	else if (r >= half && r < last) {
		if (c >= 0 && c < half) {
			return func(n - 1, r - half, c, first + diff * 2);
		}
		else if (c >= half && c < last) {
			return func(n - 1, r - half, c - half, first + diff * 3);
		}
	}

}

int main()
{
	cin >> n >> r >> c;
	int result = func(n, r, c, 0);
	cout << result;
}