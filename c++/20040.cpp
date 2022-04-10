#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

int n, m;
int* parent;
int result;

// 유니온 파인드. 처음에 각 노드의 부모를 자기 자신으로
void init()
{
	cin >> n >> m;
	parent = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		parent[i] = i;
}

void end()
{
	cout << result;
	free(parent);
}

// 노드 x의 부모 노드를 찾는다.
int find_parent(int x)
{
	if (x == parent[x])
		return x;	
	else
		return find_parent(parent[x]);
}

// 노드 x, y가 연결된다 가정. 사이클 생기면 break
// 무향 그래프에서 사이클은 x, y의 부모 노드가 같은 경우 발생
// 사이클 안 생기고 연결되면 y의 부모가 x가 된다.
void union_and_result()
{
	int x, y;
	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		x = find_parent(x);
		y = find_parent(y);

		if (x == y) {
			result = i;
			break;
		}
		parent[y] = x;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	union_and_result();
	end();
}