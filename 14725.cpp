#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

int n, k;
vector<string>foods[1001];

// 자식 노드 담을 구조체
// map 컨테이너의 count : key값 존재하면 1, 없으면 0
// 입력의 순서대로 count==1 이면 거기에 자식 노드 붙힘
// 없으면 새 노드 붙힘
struct Node {
	map<string, Node>child;
};

// 개미의 정보 입력
void init()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> k;
		for (int j = 0; j < k; j++) {
			string s;
			cin >> s;
			foods[i].push_back(s);
		}
	}
}

// vector v의 idx번째 입력을 node에 붙힘
// 해당 string이 없으면 새로 node에 붙힘
// 있으면 그 다음 string에 대해 진행
void insert(Node &node, vector<string>&v, int idx)
{
	// 리프 노드인 경우 (더 이상 붙힐 자식이 없음)
	if (idx == v.size())
		return;

	map<string, Node>::iterator iter;
	bool exit = false;

	// 해당 string 존재
	for (iter = node.child.begin(); iter != node.child.end(); iter++) {
		if (iter->first == v[idx]) {
			exit = true;
			break;
		}
	}
	// 해당 string 없음 => 새 노드 붙혀줌
	if (!exit) {
		node.child[v[idx]] = Node();
	}
	// 다음 string에 대해 진행
	insert(node.child[v[idx]], v, idx + 1);
}

// 트라이에 저장된 거 출력
// map은 기본적으로 오름차순으로 정렬
// 문제에서 사전순으로 출력하라했으므로 기본형 그대로 놔두면 됨
void dfs(Node &node, int depth)
{
	// iterator 안 쓰고 auto i : node.child 이런 식으로 해도 됨
	map<string, Node>::iterator iter;
	for (iter = node.child.begin(); iter != node.child.end(); iter++) {
		for (int idx = 0; idx < depth; idx++) {
			cout << "--";
		}
		cout << iter->first << '\n';
		dfs(iter->second, depth + 1);
	}
}

int main()
{
	init();
	Node root;

	// 입력에 대해 트리(트라이) 만들기
	for (int i = 0; i < n; i++) {
		insert(root, foods[i], 0);
	}

	// 출력
	dfs(root, 0);
}

