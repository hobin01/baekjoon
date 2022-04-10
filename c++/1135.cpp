#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> vec[51]; // vec[i] : i가 부모인 자식 노드들

void init()
{
	cin >> n;
	int num;
	for (int i = 0; i < n; i++) {
		cin >> num;
		if (num == -1)
			continue;
		vec[num].push_back(i);
	}
}

int dfs(int node, int parent)
{
	int ret = 0;

	vector<int>result; 
	// 각 자식 노드가 루트가 되는 서브트리의 결과 

	for (auto child : vec[node]) {
		int child_ret = dfs(child, node);
		result.push_back(child_ret);
	}

	// 결과 큰 애부터 먼저 전파시켜야함
	sort(result.rbegin(), result.rend());

	for (int i = 0; i < result.size(); i++) {
		ret = max(ret, result[i] + i + 1);
	}

	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	
	cout << dfs(0, -1);
}