#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m;
long long a, b;

struct bus {
	long long start;
	long long last;
	long long len;
	int idx;
};

vector<bus> vec;
vector<int> result;

// 가장 긴 애의 시작점을 기준으로 새로운 버스들 만들기
// 시작점 작은 순, 마지막 큰 순으로 정렬하고
// 앞에 거보다 마지막이 작으면 최종적으로 포함 안 시킴 

bool comp(bus& b1, bus& b2) {
	if (b1.start != b2.start)
		return b1.start < b2.start;
	else
		return b1.last > b2.last;
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	cin >> m;

	long long max_len = 0;
	int max_idx = 0;
	long long new_start = 0;

	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		bus B = { a, b, 0, i };

		if (a <= b) {
			B.len = b - a;
		}
		else {
			B.len = n + b - a;
			B.last = n + b;
		}

		vec.push_back(B);

		// 길이 더 긴 거 나타남
		if (B.len > max_len) {
			max_len = B.len;
			max_idx = B.idx;
			new_start = B.start;
		}
		else if (B.len == max_len) {
			// 길이 같으면 시작점 더 작은 거 우선
			// 길이 같고 시작점 같은 거 없음
			if (vec[max_idx - 1].start > B.start) {
				max_len = B.len;
				max_idx = B.idx;
				new_start = B.start;
			}
		}
	}

	// 가장 긴 거의 시작점 기준으로 새로 만들기
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i].start < new_start) {
			vec[i].start = vec[i].start + n;
			vec[i].last = vec[i].last + n;
		}
	}

	// 시작점 빠른 순, 길이 긴 순으로 정렬 
	sort(vec.begin(), vec.end(), comp);

	// 계산 (앞에 거보다 result 마지막이 작으면 포함 안 시킴)
	result.push_back(vec[0].idx);
	long long prev_last = vec[0].last;
	long long now_last = 0;

	for (int i = 1; i < vec.size(); i++) {
		now_last = vec[i].last;
		if (now_last > prev_last) {
			result.push_back(vec[i].idx);
			prev_last = now_last;
		}
	}

	sort(result.begin(), result.end());

	for (auto r : result) {
		cout << r << ' ';
	}
}