#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

int a, b, c;
int dp[21][21][21];
int result;

void output()
{
	printf("w(%d, %d, %d) = %d\n", a, b, c, result);
}

int w(int a, int b, int c)
{
	int &res = dp[a][b][c];
	if (a <= 0 || b <= 0 || c <= 0)
		return 1;
	if (a > 20 || b > 20 || c > 20)
		return w(20, 20, 20);

	if (res != 0)
		return res;

	if (a < b && b < c)
		res = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
	else
		res = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
	return res;
}

int main()
{
	while (1)
	{
		cin >> a >> b >> c;
		if (a == -1 && b == -1 && c == -1)
			break;

		result = w(a, b, c);
		output();
		
	}
}