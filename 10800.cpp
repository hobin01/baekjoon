#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

typedef unsigned int uint;

uint n;
vector<pair<pair<uint, uint>,uint>>ball; // {크기, 색}, 번호
uint same_color[200001]; // 같은 색 총합
uint bigger_size[2001]; // 공 크기 이상 합
uint result[200001]; // 결과
uint sum; // 전체 총합

void init()
{
	cin >> n;
	ball.push_back({ {0,0},0 });
	for (uint i = 1; i <= n; i++) {
		uint c, s;
		cin >> c >> s;
		ball.push_back({ {s,c},i });
	}

	// 크기 오름차순 정렬 (O(nlogn))
	sort(ball.begin(), ball.end());

	sum = 0;
}

// 각 공의 점수
// 전체 누적합 - (공과 색 같은 것 합 + 공 크기 이상인것 합 - 공과 색 같고 크기 이상인 것 합)

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	for (int i = 1; i <= n; i++) {
		uint size = ball[i].first.first;
		uint color = ball[i].first.second;
		uint idx = ball[i].second;

		same_color[color] += size;
		bigger_size[size] += size;
		sum += size;

		result[idx] = sum - (same_color[color] + bigger_size[size] - size);

		// 이전 것과 색, 크기 같은 경우
		// 같은 결과 가져야함
		if (i != 1) {
			if (size == ball[i - 1].first.first) {
				if (color == ball[i - 1].first.second) {
					uint tmp = ball[i - 1].second;
					result[idx] = result[tmp];
				}
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		cout << result[i] << '\n';
	}
}