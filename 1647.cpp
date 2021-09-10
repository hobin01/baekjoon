#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int a, b, c;

typedef struct edge {
	int dist;
	int from;
	int to;
}edge; // 거리, 출발, 도착

vector<edge>vec; // 간선 모은 벡터, 나중에 거리 오름차순으로 정렬해서 사용
int parent[100001];
int result;

// vec sort 할 때 기준 (가중치 오름차순)
bool cmp(const edge& a, const edge& b)
{
	if (a.dist < b.dist)
		return true;
	else if (a.dist == b.dist) {
		if (a.from < b.from)
			return true;
		else if (a.from == b.from)
			if (a.to < b.to)
				return true;
	}
	return false;
}

// 크루스칼 알고리즘 이용한 MST
// 경로를 모두 오름차순 정렬 후 사이클 안 생기게 이어준다.
// 가중치 가장 큰 간선은 제외 (해당 부분 잘라서 마을 2개 만들면 됨)

void init()
{
	cin >> n >> m;
	while (m--) {
		cin >> a >> b >> c;
		edge e = { c, a, b };
		vec.push_back(e);
	}
	result = 0;
}

// 부모 노드 초기화
void init_parent()
{
	for (int i = 0; i <= n; i++) {
		parent[i] = i;
	}
}

// 노드 x의 최상위 부모 노드 찾기
int find_parent(int x)
{
	if (x == parent[x])
		return x;
	else {
		parent[x] = find_parent(parent[x]);
		return parent[x];
	}
}

// 노드 x와 노드 y의 부모 노드 합치기
void union_parent(int x, int y)
{
	int p_x = find_parent(x);
	int p_y = find_parent(y);

	parent[p_y] = p_x;
}

// 노드 x, 노드 y 이으면 사이클 생기는지 판단
bool is_cycle(int x, int y)
{
	int p_x = find_parent(x);
	int p_y = find_parent(y);
	if (p_x == p_y)
		return true; // 사이클 발생
	else
		return false; // 사이클 발생 X
}

// vec 가중치 기준 오름차순 정렬
void sorting_vec()
{
	sort(vec.begin(), vec.end(), cmp);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	sorting_vec();

	init_parent();

	int x, y, d;
	int max_possible_dist = 0; // 연결 가능한 간선 가중치 중 최댓값
	for (int i = 0; i < vec.size(); i++) {
		x = vec[i].from;
		y = vec[i].to;
		d = vec[i].dist;

		if (parent[x] != parent[y]) {
			if (is_cycle(x, y))
				continue;

			union_parent(x, y);
			result += d;
			max_possible_dist = d;
		}
	}

	result -= max_possible_dist;
	cout << result;
}