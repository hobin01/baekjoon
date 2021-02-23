#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

int n, m;
int map[1001][1001];

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < s.size(); j++) {
			map[i][j] = s[j] - '0';
		}
	}

	// 점화식 : map[i][j] = min(map[i-1][j-1], min(map[i-1][j], map[i][j-1])) + 1
	// 왼쪽 대각선 위로 정사각형을 만들 때 dp를 이용해
	// 가능한 최대 크기(한 변 길이)를 구한다고 생각 
	// map[i][j]=0 이면 정사각형 만들기 불가
	int result = 0;
	for (int i = 0; i < n; i++)
		if (map[i][0] != 0)
			result = 1;

	for (int j = 0; j < m; j++)
		if (map[0][j] != 0)
			result = 1;

	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (map[i][j] != 0 && map[i - 1][j - 1] != 0 && map[i][j - 1] != 0 && map[i - 1][j] != 0) {
				map[i][j] = min(map[i - 1][j - 1], min(map[i - 1][j], map[i][j - 1])) + 1;
				result = max(map[i][j], result);
			}
		}
	}

	cout << result * result;
}