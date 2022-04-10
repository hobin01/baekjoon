#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int n;
bool prime[1000000];
vector<int>odd_prime;

void make_prime()
{
	memset(prime, true, sizeof(prime));
	prime[0] = false;
	prime[1] = false;
	
	for (int i = 2; i < 1000000; i++) {
		if (prime[i]) {
			for (int j = 2; j * i < 1000000; j++) {
				prime[j * i] = false;
			}
		}
	}

	for (int i = 0; i < 1000000; i++) {
		if (prime[i]) {
			odd_prime.push_back(i);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_prime();
	while (1)
	{
		cin >> n;
		if (n == 0)
			break;

		int a = 0;
		int b = 0;

		for (int i = 0; i < odd_prime.size(); i++) {
			if (prime[n - odd_prime[i]]) {
				a = odd_prime[i];
				b = n - a;
				break;
			}
		}

		cout << n << " = " << a << " + " << b << '\n';
	}
}