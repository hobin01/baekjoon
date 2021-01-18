#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

int m, n;
vector<int>larva;

void init_and_grow()
{
	cin >> m >> n;
	larva.resize(2 * m - 1, 1);

	for (int i = 0; i < n; i++) {
		int zero, one, two;
		cin >> zero >> one >> two;

		// 가장 자리 부분만 계산
		// 0일 때는 더하는 것 없음
		// 성장세가 감소하는 경우 없으므로
		// 무조건 0번째 열을 제외한 열은 다 같은 값 가짐
		for (int j = zero; j < zero + one; j++)
			larva[j]++;
		for (int j = zero + one; j < larva.size(); j++)
			larva[j] += 2;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init_and_grow();

	for (int i = 0; i < m; i++) {

		cout << larva[m - i - 1] << ' ';
		for (int j = 1; j < m; j++) {
			cout << larva[m + j - 1] << ' ';
		}
		cout << '\n';
	}
}