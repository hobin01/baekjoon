#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int T;
int n;
vector<int>num;
bool check[1001];

int cycle(vector<int>v, int n)
{
	for (int i = 1; i <= n; i++)
		check[i] = false;

	int res = 0;

	for (int i = 1; i <= n; i++)
	{
		if (check[i] == true)
			continue;

		int idx = i;
		check[idx] = true;
		while (1)
		{
			idx = v[idx];
			if (check[idx] == true)
				break;
			check[idx] = true;
		}
		res++;
	}
	return res;
}


int main()
{
	cin >> T;
	while (T--)
	{
		cin >> n;
		num.push_back(0);
		for (int i = 0; i < n; i++)
		{
			int k;
			cin >> k;
			num.push_back(k);
		}

		cout << cycle(num, n) << '\n';
		num.clear();

	}
}