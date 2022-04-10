#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;

ll N, K, M;

ll dp[2000][2000];
// combination 값 저장용
// m 최대값 2000 이므로 2000 진수라 해도 계수는 0 ~ 1999
///////////////////////////////
// Lucas Theorem
// nCr % p = Pi(i = 0 to k) (n_i, k_i) (mod p)
// where n = n_k * p^k + n_(k-1) * p^(k-1) + ... + n_0 
// r = r_k * p^k + r_(k-1) * r^(k-1) + ... + r_0
// if n_i < k_i => combination (n_i, k_i) = 0

void init()
{
	// m은 소수
	// Lucas theorem 이용
	cin >> N >> K >> M;

	fill(&dp[0][0], &dp[1999][2000], -1);
}

// nCr % m 구하기
ll combination(ll n, ll r, ll m)
{
	if (dp[n][r] != -1) {
		return dp[n][r];
	}

	if (n < r) {
		dp[n][r] = 0;
	}
	else if (n == r || r == 0) {
		dp[n][r] = 1;
	}
	else {
		dp[n][r] = combination(n - 1, r - 1, m) + combination(n - 1, r, m);
		dp[n][r] %= m;
	}

	return dp[n][r];
}

// m진법 구하기
vector<ll> m_notation(ll num, ll m)
{
	vector<ll> vec;

	ll r; // 나머지
	while (num > 0) {
		r = num % m;
		num = num / m;
		vec.push_back(r);
	}

	return vec;
}

// nCk % m 구하기 (m은 소수)
ll Lucas(ll n, ll k, ll m)
{
	vector<ll> vec_n = m_notation(n, m);
	vector<ll> vec_k = m_notation(k, m);

	int min_size = min(vec_n.size(), vec_k.size());
	// n의 m진법 계수 개수 더 많은 경우 (n_i, k_i) = (n_i, 0) = 1 이므로 곱하면 결과 동일

	ll result = 1;

	for (int i = 0; i < min_size; i++) {
		ll n_i = vec_n[i];
		ll k_i = vec_k[i];

		result *= (combination(n_i, k_i, m) % m);

		// 더 이상 안 곱해도 됨
		if (result == 0)
			break;
	}

	return result % m;
}


int main()
{
	init();

	cout << Lucas(N, K, M);
}