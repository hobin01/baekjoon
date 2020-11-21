#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

int n, m;
vector<int>user[101];
bool check[101];
pair<int, int>result = { 987654321,987654321 }; // user, sum of dist

void make_user()
{
	cin >> n >> m;
	while (m--)
	{
		int a, b;
		cin >> a >> b;
		user[a].push_back(b);
		user[b].push_back(a);
	}
}

int bfs(int start, int end)
{
	memset(check, false, sizeof(check));
	check[start] = true;

	int Dist = 0;
	int res = 0;

	queue<pair<int, int>>q;
	q.push({ start,Dist });

	while (!q.empty())
	{
		int now = q.front().first;
		int dist = q.front().second;
		q.pop();

		if (now == end)
		{
			res = dist;
			break;
		}

		for (int i = 0; i < user[now].size(); i++)
		{
			if (!check[user[now][i]])
			{
				check[user[now][i]] = true;
				q.push({ user[now][i],dist + 1 });
			}
		}
	}

	return res;
}

int main()
{
	make_user();

	int sum;
	for (int i = 1; i <= n; i++)
	{
		sum = 0;
		for (int j = 1; j <= n; j++)
		{
			if (i == j)
				continue;

			sum += bfs(i, j);
		}
		if (result.second > sum)
		{
			result = { i,sum };
		}
		if (result.second == sum)
		{
			if (result.first > i)
				result = { i,sum };
		}
	}

	cout << result.first;
}