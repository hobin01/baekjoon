#include<iostream>
#include<vector>
#include<cstdlib>
#include<algorithm>
#include<numeric>

typedef unsigned long long ull;
using namespace std;

ull gcd(ull a, ull b) {
	if (a < b) 
		swap(a, b);
	ull tmp = 1;
	while (b != 0) {
		tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}

int main()
{
	int n, m;

	cin >> n;
	ull* arr1;
	ull* arr2;

	arr1 = new ull[n];
	for (int i = 0; i < n; i++)
		cin >> arr1[i];

	cin >> m;
	arr2 = new ull[m];
	for (int i = 0; i < m; i++)
		cin >> arr2[i];

	ull result = 1;
	bool check = false;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			ull g_ij = gcd(arr1[i], arr2[j]);
			result *= g_ij;
			if (result >= ull(1e9)) {
				check = true;
				result %= ull(1e9);
			}
			arr1[i] /= g_ij;
			arr2[j] /= g_ij;
		}
	}

	if (check)
		printf("%09llu", result);
	else
		printf("%llu", result);
}