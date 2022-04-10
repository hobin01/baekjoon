#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// A,B 와 C,D 의 합을 계산한다.
// C,D의 합만 오름차순으로 정렬한다.
// lower_bound, upper_bound 함수를 이용해 -num 에 가까운 index를 찾는다.
// lower_bound : key와 같은 값 있으면 가장 작은 index를 구한다.
// 없으면 key보다 큰 수 중 가장 작은 원소의 index를 구한다.
// upper_bound : key보다 큰 원소 중 가장 작은 원소의 index를 구한다.
// key (여기서는 -num) 와 같은 값 존재할 때 조건 만족하므로 upper - lower를 더한다.

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	long long arr[4000][4];
	long long result = 0;
	vector<long long>cd;

	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cd.push_back(arr[i][2] + arr[j][3]);
		}
	}

	sort(cd.begin(), cd.end());

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			long long num = arr[i][0] + arr[j][1];
			long long lower = lower_bound(cd.begin(), cd.end(), (-1) * num) - cd.begin();
			long long upper = upper_bound(cd.begin(), cd.end(), (-1) * num) - cd.begin();

			if ((-1) * num == cd[lower])
				result += (upper - lower);
		}
	}

	cout << result;
}