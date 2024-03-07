#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// parents[node][i] : node의 2^i 번째 부모 
// 2^i 번쨰 부모 계산 : dp 이용 
// depths[node] : node 의 깊이

int n, m;
vector<int> tree[100001];
int parents[100001][20] = { {0, }, };
int depths[100001] = {0, };
int result = 0;

void init()
{
	cin >> n;
	int a, b;
	for(int i = 0; i < (n-1); i++) {
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	
	return;
}

void make_tree()
{
	int node, next_node;
	int height = 0;
	int brothers = 0;
	
	queue<int> q;
	q.push(1);
	parents[1][0] = 1; // 1 부모 1 
	 
	while(!q.empty()) {
		if(brothers == 0) {
			// 부모의 형제 노드 탐색 완료 
			brothers = q.size();
			height++;
		}
		
		node = q.front();
		q.pop(); 
		
		for(auto v : tree[node]) {
			next_node = v;
			
			// 부모 이미 아는 경우  
			if(parents[next_node][0] != 0)
				continue;
				
			parents[next_node][0] = node;
			depths[next_node] = height;
			q.push(next_node);
		}
		
		brothers--;
	}
	
	return;
}

void calc_ith_parents()
{
	for(int i = 1; i < 20; i++) {
		for(int node = 2; node <= n; node++) {
			// node 의 2^i 번쨰 부모 = 2^(i-1) 번쨰 부모의 2^(i-1) 번쨰 부모  
			parents[node][i] = parents[ parents[node][i-1] ][i-1];
		}
	}
	
	return;
}

void game(int node1, int node2)
{
	// node1, node2 대상으로 2^i 씩 올라가면서 부모 depth 맞추기 
	// ex. depth 3 차이 시, 2^1 후 2^0 번째 부모에서 일치 
	// 이후 2^i 씩 depth 올리기 
	
	// 둘 중 하나 1인 경우 
	if(node1 == 1 || node2 == 1) {
		result = 1;
		return;
	}
	
	// 노드 일치 
	if(node1 == node2) {
		result = node1;
		return;
	} 
	
	// 둘 중 하나가 부모 
	if(node1 == parents[node2][0]) {
		result = node1;
		return;
	}
	
	if(node2 == parents[node1][0]) {
		result = node2;
		return;
	}
	
	// 부모 일치 
	if(parents[node1][0] == parents[node2][0]) {
		result = parents[node1][0];
		return;
	}
	
	// 기준 : node1 이 더 아래 
	if(depths[node1] < depths[node2]) {
		swap(node1, node2);
	}
	
	// depth 맞추기 
	int parent_node1 = 0;
	if(depths[node1] != depths[node2]) {
		for(int i = 19; i >= 0; i--) { 
			parent_node1 = parents[node1][i];
			
			// 트리 넘어서는 경우
			if(parent_node1 == 0)
				continue;
			
			// depth 일치하는 경우 
			if(depths[parent_node1] == depths[node2]) {
				node1 = parent_node1;
				break;
			}
			// depth 올라가는 경우 (값 작은 경우) 
			if(depths[parent_node1] < depths[node2])
				continue;
			
			node1 = parent_node1;
		}
	}
	
	// 찾아진 경우 
	if(node1 == node2) {
		result = node1;
		return;
	} 
	
	// 2^i 씩 올려보기 
	for(int i = 19; i >= 0; i--) {
		// 트리 넘는 경우 
		if(parents[node1][i] == 0 || parents[node2][i] == 0)
			continue;
		
		// 일치하는 경우, 더 짧은 부모 있을 수 있음 
		if(parents[node1][i] == parents[node2][i]) 
			continue;
		
		node1 = parents[node1][i];
		node2 = parents[node2][i];
	}
	
	result = parents[node1][0];
	return;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	
	init();
	make_tree();
	calc_ith_parents();
	
	cin >> m;
	int node1, node2;
	while(m--) {
		cin >> node1 >> node2;
		game(node1, node2);
		cout << result << '\n';
	}
} 