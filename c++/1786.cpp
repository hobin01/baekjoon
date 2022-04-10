#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

string T, P;
vector<int>pi; // 전처리용
vector<int>result; // 정답 인덱스 저장

void make_text()
{
	getline(cin, T);
	getline(cin, P);
}

// pi배열 얻기
void get_pi(string p)
{
	int m = p.size();
	int j = 0;

	pi.resize(m, 0);

	// 한자리 글은 prefix = suffix라 하지 않으므로 i=1부터
	for (int i = 1; i < m; i++) {
		while ((j > 0) && (p[i] != p[j])) {
			j = pi[j - 1];
		}
		if (p[i] == p[j]) {
			j++;
			pi[i] = j;
		}
	}
}

// kmp 알고리즘
void kmp(string t, string p)
{
	int n = t.size();
	int m = p.size();
	int j = 0;

	for (int i = 0; i < n; i++) {
		while ((j > 0) && (t[i] != p[j])) {
			j = pi[j - 1];
		}
		if (t[i] == p[j]) {
			if (j == (m - 1)) {
				result.push_back(i - m + 1);
				j = pi[j];
			}
			else {
				j++;
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	make_text();
	get_pi(P);
	kmp(T, P);

	cout << result.size() << '\n';

	// 문제에서 인덱스 1부터 시작, kmp는 0부터 시작
	for (int i = 0; i < result.size(); i++)
		cout << result[i] + 1 << '\n';
}