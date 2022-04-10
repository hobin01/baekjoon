#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<string>

using namespace std;

string s;
int len; // s의 길이, '.'포함
bool pelin[2501][2501]; // pelin[x][y] : index가 x부터 y까지가 펠린드롬이면 true, 아니면 false
int dp[2501]; // dp[i] : i번째까지 펠린드롬 최소 개수
// dp[i] = min(dp[i], dp[j-1]+1) 
// j : i부터 1까지 돌면서 펠린드롬이면 직전값+1로 업데이트

void init()
{
	cin >> s;
	s.insert(0, "."); 
	// 맨 앞에 '.' 추가 : 맨 처음문자까지 돌았을 때 펠린드롬이면 dp[0]=0으로 생각 
	len = s.size();
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			pelin[i][j] = false;
		}
		dp[i] = 987654321;
	}
}

bool is_pelindrom(int start, int last)
{
	int mid = (start + last) / 2; // 가운데값
	int i = 0;
	bool check = true;
	while ((start + i) <= mid) {
		if (s[start + i] != s[last - i]) {
			check = false;
			break;
		}

		i++;
	}
	return check;
}

void make_pelindrom()
{
	for (int i = 1; i < len; i++) {
		for (int j = i; j < len; j++) {
			if (is_pelindrom(i, j))
				pelin[i][j] = true;
		}
	}
}

void calculate_dp()
{
	dp[0] = 0;
	dp[1] = 1;

	for (int i = 2; i < len; i++) {
		for (int j = i; j > 0; j--) {
			if(pelin[j][i])
				dp[i] = min(dp[i], dp[j - 1] + 1);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	make_pelindrom();
	calculate_dp();
	cout << dp[len - 1];
}

