#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

typedef long long ll;

int n;
// n개 입력에 대해 a,c,b 값 저장
ll a[20001];
ll b[20001];
ll c[20001];

void init()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> c[i] >> b[i];
	}
}

// f(x) : n개 입력에 대해 x 이하의 수의 개수
// n개 입력에 대해 돌면서
// a[i]가 시작점, c[i]가 최댓값, b[i]가 간격이므로
// i번째 입력에서의 x 이하의 수의 개수 = max(0, (min(x,c[i])-a[i])/b[i] + 1)
// ex) i번째 입력 a=2 c=300 b=3, x=120
// 2, 5, 8, ....., 299
// 위 수열에서 120 이하인 수의 개수 : 40개 (2, 5, ..., 119)
// min(120,300) = 120, 120-2=118, 118/3=39, 39+1=40
// 이렇게 n개 입력에 대해 다 더한 값 f(x)가 홀수면 x이하에 답 존재
// 짝수면 아직 안 나옴 => x 이후에 답 존재 
// 이분 탐색으로 가능한 x 범위 좁혀나가기
// f(x)-f(x-1) 이 홀수면 x가 정답, 개수는 f(x)-f(x-1)
// f(x)-f(x-1) 이 짝수면 홀수개인 것은 없음
ll func(ll x)
{
	ll sum = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] > x)
			continue;
		sum += ((min(x, c[i]) - a[i]) / b[i] + 1ll);
	}
	return sum;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	ll inf = 1ll << 32;
	ll left, right, mid;
	left = 0;
	right = inf;
	mid = (left + right) >> 1;

	// 이분 탐색
	while (1)
	{
		if (left >= right)
			break;

		ll sum = func(mid);
		if (sum & 1) {
			right = mid;
			mid = (left + right) >> 1;
		}
		else {
			left = mid + 1;
			mid = (left + right) >> 1;
		}
	}

	// x 위치 정해짐
	ll answer = func(left) - func(left - 1);

	// left가 해당 범위 밖이면 정답 없음
	if (left==inf) {
		cout << "NOTHING";
	}
	else {
		cout << left << ' ' << answer;
	}
}