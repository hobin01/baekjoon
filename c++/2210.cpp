#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <string>

using namespace std;

int numbers[5][5];
int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,1,-1 };
set<int> s;

void init()
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> numbers[i][j];
		}
	}
}

void bfs(int y, int x)
{
	queue<pair<string, pair<int, int>>>q;
	int num = numbers[y][x];
	string start = "";
	start += '0' + num;
	q.push({ start, {y, x} });

	while (!q.empty()) {
		string str = q.front().first;
		int y = q.front().second.first;
		int x = q.front().second.second;
		q.pop();

		if (str.size() == 6) {
			s.insert(stoi(str));
			continue;
		}

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny < 0 || ny >= 5 || nx < 0 || nx >= 5)
				continue;

			string str2 = str;
			str2 += '0' + numbers[ny][nx];
			q.push({ str2, {ny, nx} });
		}
	}
}

int main()
{
	init();
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			bfs(y, x);
		}
	}

	cout << s.size();
}