#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int main()
{
	int f, s, g, u, d;
	string fail = "use the stairs";
	vector<bool>check;
	int result = -1;
	int now = 0;
	int cnt = 0;

	cin >> f >> s >> g >> u >> d;
	check.resize(f + 1, false);
	
	queue<pair<int, int>>q;
	q.push({ s,0 });
	check[s] = true;

	while (!q.empty())
	{
		now = q.front().first;
		cnt = q.front().second;
		q.pop();

		if (now == g) {
			result = cnt;
			break;
		}

		if ((now + u) >= 1 && (now + u) <= f) {
			if (!check[now + u]) {
				q.push({ now + u,cnt + 1 });
				check[now + u] = true;
			}
		}

		if ((now - d) >= 1 && (now - d) <= f) {
			if (!check[now - d]) {
				q.push({ now - d,cnt + 1 });
				check[now - d] = true;
			}
		}
	}

	if (result == -1)
		cout << fail;
	else
		cout << result;
}