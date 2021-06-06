#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int k, n;
	map<long long, bool>check; // 중복 제거용
	vector<long long>num; // 주어진 수
	priority_queue<long long, vector<long long>, greater<long long>>q; // 우선순위 큐 오름차순

	cin >> k >> n;
	for (int i = 0; i < k; i++) {
		long long p;
		cin >> p;
		num.push_back(p);
	}

	// 1을 우선순위 큐에 넣은 다음
	// 우선순위 큐의 top원소와 num의 값을 계속 곱해나감
	// 그럼 num의 곱으로 이루어진 우선순위 큐 만들 수 있음
	// ex. 큐 : 1 => 큐 : 2 3 5 7
	// => 2 * (2, 3, 5, 7), 3 * (2, 3, 5, 7), ... 을 큐에 (기존 큐의 원소는 pop) 
	// => 큐 :  4 6 9 10 14 ...
	// N번 돌리면 top이 구하고자 하는 값 (중복 제거해야 딱 n번 돌아감)
	// 큐에 N개 이상 and max값보다 크면 들어갈 필요 없음 => 어짜피 N번째 뒤의 수

	q.push(1);
	check[1] = true;
	long long max_value = 0;

	while (n--) {
		long long now = q.top();
		q.pop();

		for (auto i : num) {
			long long next = now * i;

			// next가 이미 쓰인 경우 : 중복인 경우 : 패스
			if (check.count(next)) {
				continue;
			}

			// 큐에 n개 넘게 있고 max 값보다 큰 값이 들어오려고 하면
			// 그 녀석은 어짜피 n번째 뒤의 값 : 패스
			if (q.size() > n) {
				if (max_value <= next) {
					continue;
				}
			}

			// 나머지 : 큐에 들어올 수 있는 경우
			q.push(next);
			max_value = max(max_value, next);
			check[next] = true;
		}
	}

	cout << q.top();
}