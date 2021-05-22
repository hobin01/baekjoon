#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

int d, n;
int oven[300001];
queue<int>pizza;

void init()
{
	cin >> d >> n;
	oven[0] = 1000000001; // 10억 + 1

	// 위 칸 오븐보다 반지름 크면
	// 아래 칸은 위 칸 통과 못한 피자는 못 들어옴
	for (int i = 1; i <= d; i++) {
		int depth;
		cin >> depth;
		if (depth > oven[i - 1])
			oven[i] = oven[i - 1];
		else
			oven[i] = depth;
	}

	for (int i = 1; i <= n; i++) {
		int r;
		cin >> r;
		pizza.push(r);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	int last = -1; // 마지막 피자 위치
	for (int i = d; i >= 1; i--) {
		if (pizza.front() <= oven[i]) {
			last = i;
			pizza.pop();
		}
		if (pizza.empty())
			break;
	}

	if (pizza.empty()) {
		cout << last;
	}
	else
		cout << 0;
}