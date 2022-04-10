#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

bool check[10000];
bool prime[10000];
int res;

void make_prime()
{
	memset(check, false, sizeof(check));
	memset(prime, true, sizeof(prime));
	prime[0] = false;
	prime[1] = false;
	for (int i = 2; i < 10000; i++) {
		for (int j = 2; j * i < 10000; j++) {
			prime[j * i] = false;
		}
	}
}

void bfs(int start, int end)
{
	queue<pair<int, int>>q;
	q.push({ start,0 });
	res = -1;

	while (!q.empty()) {

		int num = q.front().first;
		int cnt = q.front().second;
		q.pop();
		check[num] = true;

		if (num == end)
		{
			res = cnt;
			return;
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 10; j++) {
				string s = to_string(num);
				s[i] = j + '0';

				int next = stoi(s);
				if (next < 1000 || next >= 10000)
					continue;
				if (check[next])
					continue;
				if (!prime[next])
					continue;

				q.push({ next,cnt + 1 });
			}
		}
	}
}

int main()
{
	int T;
	cin >> T;

	make_prime();

	while (T--)
	{
		memset(check, false, sizeof(check));
		int start, end;
		cin >> start >> end;

		bfs(start, end);
		if (res == -1)
			cout << "impossible" << '\n';
		else
			cout << res << '\n';
	}
}