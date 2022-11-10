#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// x1+...+x(m-1) = n 이 되는 경우의 수
// xi >= 1
// 결국 (m-1)H(n-(m-1)) 구하는 문제
// = (n-1)C(m-2) % 100007 구하면 됨
// 100007 = 97 * 1031
// x = (n-1)C(m-2) 라 하면
// x % 97, x % 1031 해서 나온 값을 중나정으로 계산하면 됨
// x % 97, x % 1031 할 때는 루카스 정리 이용
// 루카스 정리 쓸 때 이항계수 부분 계산은 대략 1000번 정도 곱하기 드므로
// 그냥 곱하면서 모듈로 연산해도 될 듯?
// 이항계수 분모 부분은 inverse 구해서 곱하기

vector<int> convert(int num, int m)
{
	// num을 m진법 변환
	vector<int> vec;
	while (num > 0) {
		vec.push_back(num % m);
		num /= m;
	}

	reverse(vec.begin(), vec.end());

	return vec;
}

int inverse(int num, int p)
{
	// 확장 유클리드로 인버스 구하기 (존재 가정)
	// num^-1 mod p
	int r1 = p;
	int r2 = num;
	int t1 = 0;
	int t2 = 1;
	int q, r, t;

	while (r2 > 0) {
		q = r1 / r2;
		r = r1 % r2;
		r1 = r2;
		r2 = r;

		t = t1 - q * t2;
		t1 = t2;
		t2 = t;
	}

	if (t1 < 0)
		t1 += p;
	
	return t1;
}

int comb(int n, int r, int m)
{
	// nCr % m
	int result = 1;
	int inv = 1;
	for (int cnt = 0; cnt < r; cnt++) {
		result *= (n - cnt);
		result %= m;
		inv = inverse((r - cnt), m);
		result *= inv;
		result %= m;
	}

	return result;
}

int lucas(int n, int r, int m)
{
	// nCr % m 를 루카스 정리로 계산
	vector<int> vec_n = convert(n, m);
	vector<int> vec_r;
	vector<int> tmp = convert(r, m); // 일단 앞에 0 채우기 위해 임시 저장

	int result = 1; // 최종 루카스 정리 결과 
	int size_n = vec_n.size();
	int diff = vec_n.size() - tmp.size();
	for (int i = 0; i < diff; i++) {
		vec_r.push_back(0LL);
	}
	for (int i = 0; i < tmp.size(); i++) {
		vec_r.push_back(tmp[i]);
	}

	for (int i = 0; i < size_n; i++) {
		int num_n = vec_n[i];
		int num_r = vec_r[i];

		if (num_n < num_r) {
			// 0인 케이스. 더 이상 곱해도 0
			result = 0;
			break;
		}

		if (num_n == num_r || num_r == 0) {
			// 1인 케이스
			continue;
		}
		
		result *= comb(num_n, num_r, m);
		result %= m;
	}

	return result;
}

int CRT(vector<int> num, vector<int> m)
{
	// x = num[0] mod m0
	// x = num[1] mod m1
	// .... 를 만족하는 x = num[0] * num[1] * ... mod (m0 * m1 * ...) 구하기

	int num_size = num.size();
	vector<int> n(num_size, 0); // 중나정에서 n 역할 (ni = m0 * m1 * .. * m(n-1) * m(n+1) * ...)
	vector<int> s(num_size, 0); // 중나정에서 s 역할 (si = ni^-1 mod mi)

	int m_fac = 1;
	for (int i = 0; i < num_size; i++) {
		m_fac *= m[i];
	}
	for (int i = 0; i < num_size; i++) {
		n[i] = m_fac / m[i];
		s[i] = inverse(n[i], m[i]);
	}

	int result = 0;
	for (int i = 0; i < num_size; i++) {
		result += (num[i] * n[i] * s[i]) % m_fac;
		result %= m_fac;
	}

	return result;
}

int except(int N, int M)
{
	int ret = -1;
	// 나이 기준 예외 처리
	if (N == 0 && M == 1) {
		ret = 1;
	}

	if (N == 0 && M > 1) {
		ret = 0;
	}

	if (N == 1 && M == 2) {
		ret = 1;
	}

	if (N == 1 && M != 2) {
		ret = 0;
	}

	// 날짜 기준 예외 처리
	if (M == 1 && N == 0) {
		ret = 1;
	}

	if (M == 1 && N > 0) {
		ret = 0;
	}

	if (M == 2 && N == 0) {
		ret = 0;
	}

	if (M == 2 && N > 0) {
		ret = 1;
	}

	// 중복조합 안 나오는 케이스
	if (N - (M - 1) < 0) {
		ret = 0;
	}

	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M;
	int T;

	int mod = 100007;
	int mod1 = 97;
	int mod2 = 1031;
	
	cin >> T;
	while (T--) {
		cin >> N >> M;

		int exc = except(N, M);
		if (exc != -1) {
			cout << exc << '\n';
			continue;
		}

		int x1 = lucas(N - 1, M - 2, mod1);
		int x2 = lucas(N - 1, M - 2, mod2);

		vector<int> num;
		num.push_back(x1);
		num.push_back(x2);

		vector<int> m;
		m.push_back(mod1);
		m.push_back(mod2);

		int result = CRT(num, m);

		cout << result << '\n';
	}
}