#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std; 

int n, m;
vector<string>listen;
vector<string>see;
vector<string>result;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n >> m;

	listen.resize(n);
	for (int i = 0; i < n; i++)
		cin >> listen[i];

	sort(listen.begin(), listen.end());

	for (int i = 0; i < m; i++)
	{
		string s2;
		cin >> s2;
		bool check = binary_search(listen.begin(), listen.end(), s2);
		if (check)
			result.push_back(s2);
	}

	sort(result.begin(), result.end());
	cout << result.size() << '\n';
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << '\n';
}