#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int n, k;
priority_queue<long long> pq;
vector<long long>weight;
vector<pair<long long, long long>>jewel;
int jewel_idx;

void init()
{
	cin >> n >> k;
	vector<pair<long long, long long>> vec;
	for (int i = 0; i < n; i++) {
		long long m, v;
		cin >> m >> v;
		pair<long long, long long> p = { m, v };
		vec.push_back(p);
	}

	for (int i = 0; i < k; i++) {
		long long c;
		cin >> c;
		weight.push_back(c);
	}

	sort(weight.begin(), weight.end()); // 오름차순 정렬

	// 가장 큰 가방보다 무거운 애들 제거
	long long max_w = weight[weight.size() - 1];

	for (int i = 0; i < vec.size(); i++) {
		if (vec[i].first <= max_w)
			jewel.push_back(vec[i]);
	}

	// 보석 오름차순 정렬 (무게, 가치)
	sort(jewel.begin(), jewel.end());

	// 몇 번째 보석까지 확인했는지 체크용
	jewel_idx = 0; 
}

// 우선순위 큐에 보석 가치 내림차순되게
// 가방은 오름차순
// 가방 무게보다 가벼운 모든 보석 pq에 넣기
// 단순히 가치 합만 구하는 것이므로
// 우선순위 큐의 top에 있는 것이 현재 가방 무게에 넣을 수 있는 최대 가치

long long find_value(int idx)
{
	long long w = weight[idx];
	long long result = 0;

	for (int i = jewel_idx; i < jewel.size(); i++) {
		long long mass = jewel[i].first;
		long long value = jewel[i].second;

		if (mass <= w) {
			pq.push(value);
			jewel_idx++;
		}

		else {
			jewel_idx = i;
			break;
		}
	}

	if (pq.empty())
		return result;
	else {
		result += pq.top();
		pq.pop();
		return result;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	long long result = 0;
	for (int i = 0; i < weight.size(); i++) {
		result += find_value(i);
	}

	cout << result;
}