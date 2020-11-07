#include<iostream>
#include<vector>
#include<algorithm>
#include<memory.h>
#include<queue>
#include<string>
using namespace std;

int main()
{
	int TC;
	cin >> TC;
	while (TC--)
	{
		int inf = 987654321;
		vector < pair<pair<int, int>, int>>v;
		int dist[510];

		memset(dist, 3, sizeof(dist));

		int n, m, w;
		cin >> n >> m >> w;
		for (int i = 0; i < m; i++)
		{
			int s, e, t;
			cin >> s >> e >> t;
			v.push_back({ {s,e},t });
			v.push_back({ {e,s},t });
		}
		for (int i = 0; i < w; i++)
		{
			int s, e, t;
			cin >> s >> e >> t;
			v.push_back({ {s,e},-t });
		}

		dist[1] = 0;
		bool yes = false;

		for (int i = 1; i <= n - 1; i++)
		{
			for (int j = 0; j < v.size(); j++)
			{
				int from = v[j].first.first;
				int to = v[j].first.second;
				int cost = v[j].second;

				if (dist[to] > (dist[from] + cost))
					dist[to] = dist[from] + cost;
			}
		}

		for (int i = 0; i < v.size(); i++)
		{
			int from = v[i].first.first;
			int to = v[i].first.second;
			int cost = v[i].second;

			if (dist[to] > (dist[from] + cost))
			{
				yes = true;
				cout << "YES" << '\n';
				v.clear();
			}
		}

		if (!yes)
		{
			cout << "NO" << '\n';
			v.clear();
		}
	}
}