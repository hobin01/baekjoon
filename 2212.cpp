#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<long long>v; // 센서 리스트
vector<long long>dist; // 센서 간 거리 차 리스트
int n, k;

void init()
{
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		v.push_back(num);
	}
}

long long find_min()
{
	long long result = 0;

	// 센서 간 거리 차 구하기
	// 센서 간 거리 차 중 가장 긴 것 n-k개 합이 정답

	// 센서 오름차순 정렬
	sort(v.begin(), v.end());
	
	// 센서 거리 차 구하기
	for (int i = 0; i < (v.size() - 1); i++) {
		long long sensor1 = v[i];
		long long sensor2 = v[i + 1];

		long long d = sensor2 - sensor1;

		dist.push_back(d);
	}

	sort(dist.begin(), dist.end());

	for (int i = 0; i < (n - k); i++) {
		result += dist[i];
	}

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cout.tie(NULL);
	init();

	// k >=n : 센서에 집중국 다 달면 됨
	if (k >= n)
		cout << 0;
	else
		cout << find_min();
}