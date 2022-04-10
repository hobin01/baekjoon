#include<iostream>
#include<algorithm>

using namespace std;

int n;
int ans;
int port[40001];
int dp[40001]; 
// 부분 수열의 길이가 i인 것 중 가장 작은 마지막 값
// ex . 5 2 6 1 8 3 4 7
// 각 위치를 끝점으로 계산했을 때 가장 긴 부분수열 길이
//      1 1 2 1 3 2 3 4
// dp={ 1,3,4,7 } (1부터 index 시작) => 오름차순으로 정렬됨

void init()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int num;
		cin >> num;
		port[i] = num;
		dp[i] = 0;
	}
	ans = 0;
}

int Binary(int start, int last, int num)
{
	// dp 중에서 num보다 작은 가장 큰 값의 인덱스 구하기
	// dp는 오름차순
	int mid = (start + last) / 2;
	while (start <= last) {
		mid = (start + last) / 2;
		if (num > dp[mid]) {
			start = mid + 1;
		}
		else
			last = mid - 1;
	}
	return last;
}

void calculate()
{
	dp[1] = port[1];
	ans = 1;
	int start = 1;
	int last = 1;
	for (int i = 2; i <= n; i++) {
		// 부분 수열 길이 1인 경우
		// 이분 탐색으로 찾을 수 없는 경우
		if (port[i] < dp[1]) {
			dp[1] = port[i];
		}
		else {
			last = ans;
			int idx = Binary(start, last, port[i]);

			// 새로운 최장 부분 수열
			if (dp[idx + 1] == 0) {
				dp[idx + 1] = port[i];
				ans++;
			}
			// 같은 길이 있는 경우
			else {
				dp[idx + 1] = min(dp[idx + 1], port[i]);
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	calculate();
	cout << ans;
}