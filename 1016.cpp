#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

typedef unsigned long long ull;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ull Min, Max;
	vector<bool>check;

	cin >> Min >> Max;
	check.resize(Max - Min + 1, false);
	ull result = Max - Min + 1;

	ull idx = 2;
	while (idx*idx <= Max) {

		ull num = Min / (idx*idx);
		if ((Min % (idx*idx)) != 0) {
			num++;
		}

		while ((num * (idx*idx)) <= Max) {
			ull tmp = num * (idx*idx) - Min;
			if (!check[tmp]) {
				check[tmp] = true;
				result--;
			}
			num++;
		}
		idx++;
	}

	cout << result;
}