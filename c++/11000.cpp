#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int n, s, t;
vector<pair<int, int>>vec; // {시작 시간, 끝 시간}
int res;

void init()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s >> t;
		vec.push_back({ s, t });
	}
	res = 0;
}

void sorting()
{
	sort(vec.begin(), vec.end()); // 시작 시간 빠른 순, 끝 시간 빠른 순
}

void result()
{
	priority_queue<int, vector<int>, greater<int>> pq;
	// 우선 순위 큐에 끝나는 시간 빠른 순으로 넣음
	// 그럼 시작 시간 빠른 순으로 입력 들어오면서 
	// 우선순위 큐의 top 원소인 끝나는 시간보다 빠르면
	// 새로운 원소로(끝나는 시간을), 
	// 느리거나 같으면 
	// 그 수업 끝나고 이어서 할 수 있는 거니 pop 하고 
	// 새로운 원소로(끝나는 시간을)

	pq.push(vec[0].second);

	for (int i = 1; i < n; i++) {
		int end_time = pq.top();
		int new_start_time = vec[i].first;
		int new_end_time = vec[i].second;
		if (end_time > new_start_time) {
			// 들어갈 수업 없음
			pq.push(new_end_time);
		}
		else {
			// 들어갈 수업 있음
			pq.pop();
			pq.push(new_end_time);
		}
	}

	res = pq.size();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	sorting();
	result();
	cout << res;
}