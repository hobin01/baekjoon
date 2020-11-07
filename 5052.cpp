#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

int t, n;
vector<string>num;

bool consistent(vector<string>v)
{
	bool res = true;

	for (int i = 0; i < v.size() - 1; i++)
	{
		if (res == false)
			break;

		string check = v[i];
		int size = check.size();
		string next = v[i + 1].substr(0, size);

		if (check == next)
		{
			res = false;
			break;
		}
	}
	return res;
}

int main()
{
	cin >> t;
	while (t--)
	{
		num.clear();
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			string s;
			cin >> s;
			num.push_back(s);
		}

		sort(num.begin(), num.end());
		if (consistent(num))
			cout << "YES" << '\n';
		else
			cout << "NO" << '\n';
	}
}