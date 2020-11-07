#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int n;
int p1, p2;
int rel;
vector<int>v[101];
bool check[101];
int ans = -1;

void dfs(int start, int end, int cnt)
{
	check[start] = true;
	if (start == end)
	{
		ans = cnt;
		return;
	}

	for (int k = 0; k < v[start].size(); k++)
	{
		if (!check[v[start][k]])
			dfs(v[start][k], end, cnt + 1);
	}
	return;
}


int main()
{
	cin >> n;
	cin >> p1 >> p2;
	cin >> rel;

	for (int i = 0; i < rel; i++)
	{
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
		check[i + 1] = false;
	}

	dfs(p1, p2, 0);
	cout << ans;
}