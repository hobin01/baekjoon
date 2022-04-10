#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int n, m;
int a, b;
int t;
int result;

// 끝 번호 순으로 정렬
// 끝 번호 같으면 범위 작은 거 순으로 정렬
// 그리고 하니씩 체크

typedef struct info {
	int a;
	int b;
	int len;
}info;

vector<info>v;

void init()
{
	v.clear();
	result = 0;

	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		info inf = { a, b, b - a + 1 };
		v.push_back(inf);
	}
}

bool compare(info& info1, info& info2) 
{
	// 끝 번호 같으면 길이 오름차순
	if (info1.b == info2.b) {
		return info1.len < info2.len;
	}

	// 나머지 끝 번호 오름차순
	return info1.b < info2.b;
}

void sort_vec()
{
	sort(v.begin(), v.end(), compare);
}

void check_max()
{
	bool check[1001];
	memset(check, false, sizeof(check));
	// 이미 줬으면 true, 아니면 false

	for (auto inf : v) {
		int start = inf.a;
		int last = inf.b;

		for (int num = start; num <= last; num++) {
			if (check[num] == false) {
				check[num] = true;
				result++;
				break;
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> t;

	while (t--) {
		init();

		sort_vec();

		check_max();

		cout << result << '\n';
	}
}