#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <cmath>

using namespace std;

int T;
long long A, B;
bool is_prime[2000001];
int max_num = 2000001;
vector<long long>primes;

void init()
{
	cin >> A >> B;
}

void yes()
{
	cout << "YES";
}

void no()
{
	cout << "NO";
}

void Eratos()
{
	memset(is_prime, true, sizeof(is_prime));

	for (int i = 2; i * i < max_num; i++) {
		if (is_prime[i] == true) {
			for (int j = i * i; j < max_num; j += i)
				is_prime[j] = false;
		}
	}

	for (int i = 2; i < max_num; i++) {
		if (is_prime[i] == true)
			primes.push_back((long long)i);
	}
}

bool check_prime(long long num)
{
	bool check = true;
	for (int i = 0; i < primes.size(); i++) {
		if (num <= primes[i])
			break;

		if (num % primes[i] == 0) {
			check = false;
			break;
		}
	}
	return check;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// 골드바흐 추측이 참이라 가정하고
	// 짝수일 때는 항상 참 (2 제외)
	// 홀수 = 홀수 + 짝수
	// 결국 A+B - 2가 소수면 true 아니면 false
	
	// 밀러 라빈 쓰니까 틀렸다 그럼 (수도 프라임이지만 합성수인게 테스트 케이스에 있는 듯)
	// 에라토스테네스 체를 쓰자
	// 최대 4조니까 2백만까지만 에라토스테네스체로 구하자

	Eratos();

	cin >> T;
	while (T--) {

		init();

		long long sum = A + B;

		if (sum <= 3) // 무조건 안 됨
			no();
		else if ((sum & 1) == 0) // 2보다 큰 짝수
			yes();
		else {
			// 2보다 큰 홀수
			// 무조건 2 + 소수 꼴
			long long num = sum - 2;
			if (check_prime(num))
				yes();
			else
				no();
		}

		if (T != 0)
			cout << '\n';
	}
}