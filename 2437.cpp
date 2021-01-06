#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int n;
vector<int>v;
void weight()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int num;
		cin >> num;
		v.push_back(num);
	}
	sort(v.begin(), v.end());
}

int main()
{
	weight();
	int res = 1;

	if (v[0] > 1) {
		cout << res;
		return 0;
	}

	for (int i = 1; i < n; i++) {
		if (v[i] > res + 1)
			break;
		res += v[i];
	}
	cout << res + 1;
}