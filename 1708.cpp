#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

typedef long long ll;

typedef struct info {
	ll x, y; // 실제 위치
	ll p, q; // 기준점으로부터 상대 위치
}info;

int n;
vector<info>dots;
stack<int>st;

void init()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		ll x, y;
		cin >> x >> y;
		dots.push_back({ x, y, (ll)0, (ll)0 });
	}
}

bool compare_yx(const info& dot1, const info& dot2)
{
	// y좌표, x좌표 작은 순으로 정렬
	if (dot1.y != dot2.y) {
		return dot1.y < dot2.y;
	}
	else {
		return dot1.x < dot2.x;
	}
}

bool compare_counter_clock(const info& dot1, const info& dot2)
{
	// 기준점으로부터 반시계 방향 정렬
	if (dot1.p * dot2.q != dot1.q * dot2.p) { 
		// 기준점 (0,0) 잡았을 때 dot1, dot2 벡터를 외적한 걸로
		// 반시계 방향 판단
		// dot1 x dot2 > 0 => dot1, dot2 순
		// dot1 x dot2 = 0 => 일직선
		// dot1 x dot2 < 0 => dot2, dot1 순
		return dot1.p * dot2.q - dot1.q * dot2.p > 0;
	}
	else { 
		// 일직선인 경우
		// y, x좌표 작은 순으로 
		return compare_yx(dot1, dot2);
	}
}

void sortingDots()
{
	// y좌표, x좌표 순으로 점 정렬
	sort(dots.begin(), dots.end(), compare_yx);

	// 기준점 (0번 점) 으로부터 상대 위치 계산
	ll baseX = dots[0].x;
	ll baseY = dots[0].y; 

	for (int i = 1; i < dots.size(); i++) {
		dots[i].p = dots[i].x - baseX;
		dots[i].q = dots[i].y - baseY;
	}

	// 기준점으로부터 반시계방향 정렬
	vector<info>::iterator iter = dots.begin();
	iter++;
	sort(iter, dots.end(), compare_counter_clock);
}

bool CCW(const info& dot1, const info& dot2, const info& dot3)
{
	// 외적으로 좌회전, 우회전 판단
	// dot1, dot2, dot3 순으로 input
	// dot1 to dot2 vector v1
	// dot2 to dot3 vector v2
	// v1 x v2 > 0 => 좌회전
	// v1 x v2 < 0 => 우회전
	// v1 x v2 = 0 => 직진

	// 그라함 스캔 알고리즘에서는 ccw 좌회전 하는 경우 ( > 0 )
	// 추가 진행하므로 ccw > 0 이면 true

	return dot1.x * dot2.y + dot2.x * dot3.y + dot3.x * dot1.y - (dot1.y * dot2.x + dot2.y * dot3.x + dot3.y * dot1.x) > 0;
}

void graham()
{
	int first = 0;
	int second = 1;
	int next = 2;

	st.push(first);
	st.push(second); // 첫 번째, 두 번째 점 

	while (next < n) { // 점 다 돌 때 까지
		while (st.size() >= 2) { // 다음 점 찾기
			second = st.top();
			st.pop();
			first = st.top();

			// first, second, next ccw > 0 => second 다시 push, break
			// ccw < 0 => 다음 점 찾기

			if (CCW(dots[first], dots[second], dots[next]) == true) {
				st.push(second);
				break;
			}
		}

		// 다음 점 넣기
		st.push(next);
		next++;
	}

	// 최종 볼록 껍질은 스택에 있는 번호 순으로 연결하면 됨
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	sortingDots();

	graham();

	cout << st.size();
}