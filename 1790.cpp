#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	long long n, k;
	cin >> n >> k;

	long long res;

	long long arr[9] = { 9,180,2700,36000,450000,5400000,63000000,720000000,9 };

	long long idx = 0;
	long long tmp = 0;
	for (int i = 0; i < 9; i++)
	{
		tmp += arr[i];
		if (tmp > k)
		{
			idx = i;
			break;
		}
	}
	tmp -= arr[idx];
	k -= tmp;

	long long r = k % (idx + 1);
	long long q = k / (idx + 1);

	long long num = pow(10, idx);
	if (r == 0)
	{
		if (n < (num + q - 1))
		{
			cout << -1;
			return 0;
		}
		num += q;
		num -= 1;
		cout << num % 10;
		return 0;
	}
	else
	{
		if (n < (num + q))
		{
			cout << -1;
			return 0;
		}
		num += q;
		string ans = to_string(num);
		cout << ans[r - 1];
		return 0;
	}

}