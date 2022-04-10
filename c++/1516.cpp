#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int n;
int degree[501];
int basic[501];
int result[501];
vector<int>building[501];

void make_building()
{
	cin >> n;
	memset(degree, 0, sizeof(degree));
	memset(basic, 0, sizeof(basic));
	memset(result, 0, sizeof(result));

	for (int i = 1; i <= n; i++) {
		int time;
		cin >> time;
		basic[i] = time;

		while (1)
		{
			int node;
			cin >> node;
			if (node == -1)
				break;

			degree[i]++;
			building[node].push_back(i);
		}
	}
}

int main()
{
	make_building();
	queue<int>q;
	for (int i = 1; i <= n; i++) {
		if (degree[i] == 0)
			q.push(i);
	}

	while (!q.empty()) {
		int node = q.front();
		q.pop();

		for (int i = 0; i < building[node].size(); i++) {
			int next = building[node][i];
			result[next] = max(result[next], result[node] + basic[node]);

			degree[next]--;
			if (degree[next] == 0)
				q.push(next);
		}
	}

	for (int i = 1; i <= n; i++)
		cout << basic[i] + result[i] << '\n';
}