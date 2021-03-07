#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

char map[12][6];
bool visited[12][6];
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };

void make_map()
{
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> map[i][j];
			visited[i][j] = false;
		}
	}
}

// 터질 수 있는 뿌요 있는 지 확인 
// y,x 와 연결된 것 중에 없으면 0, 있으면 1
// 맵 전체에서 돌려서 합 0이면 게임 스탑
int Pop(int Y, int X)
{
	if (map[Y][X] == '.')
		return 0;

	else {
		char Puyo = map[Y][X];
		queue<pair<int, int>>q;
		q.push({ Y, X });
		vector<pair<int, int>>v;

		while (!q.empty()) {
			int y = q.front().first;
			int x = q.front().second;
			q.pop();
			visited[y][x] = true;
			v.push_back({ y,x });

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];

				if (ny >= 0 && ny < 12 && nx >= 0 && nx < 6) {
					if (map[ny][nx] == Puyo && visited[ny][nx] == false) {
						q.push({ ny,nx });
					}
				}
			}
		}

		if (v.size() >= 4) {
			for (int i = 0; i < v.size(); i++) {
				int y = v[i].first;
				int x = v[i].second;
				map[y][x] = '.';
			}
			v.clear();
			return 1;
		}
		else {
			v.clear();
			return 0;
		}
	}
}

// X번째 열을 통째로 검사
// 해당 열에 있는 모든 뿌요를 바닥에서부터 쌓으면 됨.
void down(int X)
{
	vector<char>v;
	for (int i = 11; i >= 0; i--) {
		if (map[i][X] != '.') {
			v.push_back(map[i][X]);
			map[i][X] = '.';
		}
	}

	int y = 11;
	for (int i = 0; i < v.size(); i++) {
		map[y][X] = v[i];
		y--;
	}
	v.clear();
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_map();

	int pop_cnt = 0;
	int result = 0;
	while (1) {

		pop_cnt = 0;
		for (int i = 0; i < 12; i++)
			for (int j = 0; j < 6; j++)
				visited[i][j] = false;

		for (int j = 0; j < 6; j++) {
			down(j);
		}

		for (int i = 11; i >= 0; i--) {
			for (int j = 0; j < 6; j++) {
				pop_cnt += Pop(i, j);
			}
		}

		if (pop_cnt > 0)
			result++;
		if (pop_cnt == 0)
			break;

	}

	cout << result;
}