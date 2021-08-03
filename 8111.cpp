#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

int T;
int N;
string res;
string fail = "BRAK";
vector<string> result;
vector<int> numbers;
bool check[20001];

void init()
{
	cin >> T;

	for (int i = 0; i < T; i++) {
		cin >> N;
		numbers.push_back(N);
	}
}

void bfs(int num)
{
	queue<pair<int, string>> q;

	q.push({ 1, "1" });

	while (!q.empty()) {

		int x = q.front().first;
		string s = q.front().second;
		q.pop();

		x %= num;

		if (s.size() > 100) {
			result.push_back(fail);
			break;
		}

		if (x == 0) {
			result.push_back(s);
			break;
		}

		if (check[(x * 10) % num] == false) {
			check[(x * 10) % num] = true;
			q.push({ (x * 10) % num, s + "0" });
		}

		if (check[(x * 10 + 1) % num] == false) {
			check[(x * 10 + 1) % num] = true;
			q.push({ (x * 10 + 1) % num, s + "1" });
		}

	}

	return;
}

void print_result()
{
	for (int i = 0; i < T; i++) {
		cout << result[i] << '\n';
	}

}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	for (int i = 0; i < T; i++) {

		memset(check, false, sizeof(check));
		bfs(numbers[i]);
	}

	print_result();
}