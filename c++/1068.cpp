#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int n;
vector<int>tree[51];
bool check[51];
int del_node;
int root;

// 부모 노드 = vector[0]
void make_tree()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int parent;
		cin >> parent;
		if (parent == -1)
			root = i;
		else {
			tree[i].push_back(parent);
			tree[parent].push_back(i);
		}
	}
	cin >> del_node;

	memset(check, false, sizeof(check));
}

// bfs로 지울 노드 제외하고 탐색하여 리프 찾기
int remove_and_find_leaf(int start)
{
	// bfs
	queue<int>q;
	q.push(start);
	check[start] = true;
	int result = 0;

	while (!q.empty()) {
		int node = q.front();
		q.pop();

		int child = 0;
		for (int i = 0; i < tree[node].size(); i++) {
			if (!check[tree[node][i]]) {
				child++;
				check[tree[node][i]] = true;
				q.push(tree[node][i]);
			}
		}

		if (child == 0)
			result++;
	}

	return result;
}

int main()
{
	make_tree();
	check[del_node] = true;
	int res = 0;
	if (!check[root])
		res = remove_and_find_leaf(root);
	cout << res;
}