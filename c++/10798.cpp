#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>

using namespace std;

int main()
{
	vector<string>v;
	for (int i = 0; i < 5; i++)
	{
		string s;
		cin >> s;
		while (s.size() != 15)
			s += "_";
		v.push_back(s);
	}
	string ans = "";

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (v[j][i] != '_')
				ans += v[j][i];
		}
	}
	cout << ans;
}