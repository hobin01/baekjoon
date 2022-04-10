#include <iostream>

using namespace std;

int t;
long long k, c;
// c^-1 mod k 구하면 됨
// 안되는 경우는 gcd(c,k)!=1 인 경우

long long gcd(long long a, long long b)
{
	long long q = a / b;
	long long r = a % b;

	while (r != 0) {
		a = b;
		b = r;
		q = a / b;
		r = a % b;
	}
	a = b;
	b = r;

	return a;
}

long long extended_euclid(long long m, long long a) 
{
	// a^-1 mod m
	long long mod = m;
	a %= m;
	long long q = m / a;
	long long r = m % a;
	long long t1 = 0;
	long long t2 = 1;
	long long t = (t1 - q * t2) % mod;
	if (t < 0)
		t += mod;

	while (r != 0) {
		m = a;
		a = r;
		t1 = t2;
		t2 = t;
		q = m / a;
		r = m % a;
		t = (t1 - q * t2) % mod;
		if (t < 0)
			t += mod;
	}

	t1 = t2;
	t2 = t;
	return t1 % mod;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> t;
	while (t--) {
		cin >> k >> c;

		if (k == 1 && c != 1) {
			cout << 1 << '\n';
			continue;
		}

		if (k != 1 && c == 1) {
			if ((k + 1) > 1e9) {
				cout << "IMPOSSIBLE\n";
				continue;
			}
			else {
				cout << k + 1 << '\n';
				continue;
			}
		}

		if (k == 1 && c == 1) {
			cout << 2 << '\n';
			continue;
		}

		if (gcd(k, c) != 1 || c % k == 0 || k % c == 0) {
			cout << "IMPOSSIBLE\n";
			continue;
		}

		c %= k;
		long long result = extended_euclid(k, c);
		
		if (result > 1e9) {
			cout << "IMPOSSIBLE\n";
		}
		else {
			cout << result << '\n';
		}
	}
}