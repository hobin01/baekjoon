#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>

using namespace std;

int n, m;
int parent[50001]; // 부모 노드
vector<int>child[50001];
int depth[50001];
bool check[50001];
int result = 1;

void make_map()
{
	cin >> n;
	memset(parent, 0, sizeof(parent));
	memset(check, false, sizeof(check));

	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		child[a].push_back(b);
		child[b].push_back(a);
	}
}

void cal_depth()
{
	queue<int>q;
	check[1] = true;
	q.push(1);

	while (!q.empty())
	{
		int p = q.front();
		q.pop();

		for (int i = 0; i < child[p].size(); i++)
		{
			int next = child[p][i];
			if (!check[next])
			{
				check[next] = true;
				depth[next] = depth[p] + 1;
				parent[next] = p;
				q.push(next);
			}
		}
	}
}

void find(int node1, int node2)
{
	if (depth[node1] > depth[node2]) // node2를 더 깊은 것으로
		swap(node1, node2);

	while (depth[node1] != depth[node2])
		node2 = parent[node2];

	while (node1 != node2)
	{
		node1 = parent[node1];
		node2 = parent[node2];
	}
	result = node1;
}

int main()
{
	make_map();
	cal_depth();

	cin >> m;
	while (m--) {
		int a, b;
		cin >> a >> b;

		result = 1;
		find(a, b);
		cout << result << '\n';
	}
}