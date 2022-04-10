#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cstring>

using namespace std;

pair<int, int>dots[21]; 
vector<vector<int>>minuses; // 20C10 결과 저장
double result; // 벡터 합 크기 최대 20만 루트2 * 10 < 400만

// 벡터를 고른 뒤 합 벡터를 구한 뒤 해당 벡터 크기 구하는 문제
// 원점을 기준으로 보면 n개 점 중 n/2는 뺄셈 적용, 나머지 n/2는 덧셈 적용
// 20C10 개의 뺄셈할 (원점 to 점) 벡터의 index 구한 뒤 계산
// 20C10 = 184756

// 20C10 구하기
void combination(vector<int>& arr, vector<int>& comb, int r, int idx, int depth)
{
	if (r == 0) {
		minuses.push_back(comb);
	}

	else if (depth == arr.size())
		return;

	else {
		comb[idx] = arr[depth];
		combination(arr, comb, r - 1, idx + 1, depth + 1);
		combination(arr, comb, r, idx, depth + 1);
	}
}

void make_combination(int n)
{
	int r = n / 2;
	vector<int>arr(n);
	vector<int>comb(r);
	for (int i = 0; i < n; i++)
		arr[i] = i;

	int idx = 0;
	int depth = 0;

	combination(arr, comb, r, idx, depth);
	arr.clear();
	comb.clear();
}

// p1, p2 거리 구하기
// 최대 20만 * 루트2
double distance(pair<int, int>p)
{
	double y = (double)p.first;
	double x = (double)p.second;

	double d = sqrt(y * y + x * x);
	return d;
}

// n/2개는 뺄셈, 나머지는 덧셈
double calculate(vector<int>& v, int n)
{
	bool check[21];
	memset(check, false, sizeof(check));

	int y = 0;
	int x = 0;

	for (int i = 0; i < v.size(); i++) {
		int idx = v[i];
		check[idx] = true;
		y -= dots[idx].first;
		x -= dots[idx].second;
	}

	for (int i = 0; i < n; i++) {
		if (check[i] == false) {
			y += dots[i].first;
			x += dots[i].second;
		}
	}

	pair<int, int>p = { y,x };

	return distance(p);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;

		for (int i = 0; i < N; i++) {
			int y, x;
			cin >> y >> x;
			dots[i] = { y,x };
		}

		result = numeric_limits<double>::max();

		minuses.clear();
		make_combination(N);

		for (int i = 0; i < minuses.size(); i++) {
			double tmp = calculate(minuses[i], N);
			result = min(result, tmp);
		}

		printf("%.6lf", result);
		printf("\n");
	}
}