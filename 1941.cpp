#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

char map[5][5];

int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };
int result = 0;

void init()
{
	for (int i = 0; i < 5; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < 5; j++) {
			map[i][j] = s[j];
		}
	}
}

// 7개 자리가 연결되었는지 확인하고 S가 4 이상인지 확인
bool bfs(vector<int>&comb)
{
	bool visited[5][5]; // 해당 위치 방문 여부
	bool check[5][5]; // 조합의 위치 인지 아닌지 체크
	memset(visited, false, sizeof(visited));
	memset(check, false, sizeof(check));

	// S가 4개 이상인지 확인
	int sum = 0;
	for (int i = 0; i < comb.size(); i++) {
		int num = comb[i];
		if (map[num / 5][num % 5] == 'S')
			sum++;
		check[num / 5][num % 5] = true;
	}

	if (sum < 4) {
		return false;
	}
	
	else {
		queue<pair<int, int>>q;
		int first = comb[0];

		q.push({ first / 5, first % 5 });
		visited[first / 5][first % 5] = true;

		int cnt = 1; // 연결 개수 카운트

		// 7개 다 연결인지 확인
		while (!q.empty())
		{
			int y = q.front().first;
			int x = q.front().second;

			q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];

				if (ny < 0 || ny >= 5 || nx < 0 || nx >= 5)
					continue;

				if (visited[ny][nx] == false) {
					if (check[ny][nx] == true) {
						visited[ny][nx] = true;
						cnt++;
						q.push({ ny,nx });
					}
				}
			}
		}

		if (cnt == 7) {
			return true;
		}
		else {
			return false;
		}
	}
}

// 조합 구할 때 [i][j] 번 자리를 4*i+j 로 생각
// 0 1 2 3
// 4 5 6 7
// ...

// 조합을 돌면서 0~24 중 7개 다 뽑은 경우
// S가 4 이상인 경우에 대해
// 모두 연결인지 확인
// 다 만족하면 result++
void combination(vector<int>&arr, vector<int>&comb, int r, int idx, int depth)
{
	// 다 뽑은 경우
	// 번호 오름차순으로 들어감
	if (r == 0) {
		if (bfs(comb))
			result++;
	}

	// 안 뽑다가 r개 못 채운 경우
	else if (depth == arr.size())
		return;

	else {
		// arr[depth] 뽑은 경우
		comb[idx] = arr[depth];
		combination(arr, comb, r - 1, idx + 1, depth + 1);

		// 안 뽑은 경우
		combination(arr, comb, r, idx, depth + 1);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	vector<int>arr(25);
	for (int i = 0; i < 25; i++) {
		arr[i] = i;
	}

	int r = 7;
	vector<int>comb(r);

	combination(arr, comb, r, 0, 0);

	cout << result;
}