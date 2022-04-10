#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>

using namespace std;

string S;
string P;
vector<int>pi;

void init()
{
	cin >> S;
	cin >> P;
}

// 전처리 pi 배열 구하기
void get_pi(string s)
{
	int m = s.size();
	int i = 0, j = 0;
	pi.resize(m, 0);

	for (int i = 1; i < m; i++) {
		while ((j > 0) && (s[i] != s[j])) {
			j = pi[j - 1];
		}
		if (s[i] == s[j]) {
			j++;
			pi[i] = j;
		}
	}
}

// kmp 알고리즘
bool kmp(string s, string p)
{
	int n = s.size();
	int m = p.size();
	int i = 0, j = 0;

	for (int i = 0; i < n; i++) {
		while ((j > 0) && (s[i] != p[j])) {
			j = pi[j - 1];
		}
		if (s[i] == p[j]) {
			if (j == m - 1) {
				return true;
				break;
			}
			else
				j++;
		}
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	get_pi(S);
	cout << kmp(S, P);
}