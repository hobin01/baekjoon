#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string s;
int result;
vector<int>pi;

void init()
{
	cin >> s;
	result = 0;
}

void Get_pi(string& str)
{
	pi.clear();
	int m = str.size();
	int i = 0;
	int j = 0;
	pi.resize(m, 0);

	for (i = 1; i < m; i++) {
		while ((j > 0) && (str[i] != str[j])) {
			j = pi[j - 1];
		}
		if (str[i] == str[j]) {
			j++;
			pi[i] = j;
		}
	}
}

// s2 가 s1의 부분문자열이면서 2번 카운트 되는지 확인 (kmp)
bool Check_Two_Count_with_KMP(string& s1, string& s2) 
{
	int n = s1.size();
	int m = s2.size();
	int i = 0;
	int j = 0;

	int cnt = 0;

	for (i = 0; i < n; i++) {
		while ((j > 0) && (s1[i] != s2[j])) {
			j = pi[j - 1];
		}
		if (s1[i] == s2[j]) {
			if (j == (m - 1)) {
				cnt++;
				j = pi[j];

				if (cnt == 2)
					return true;
			}
			else
				j++;
		}
	}

	return false;
}

// max_num : 현재까지 계산된 가장 긴 길이
// idx : 부분 문자열 시작 위치
int Find_Longest(int max_num, int idx)
{
	int n = 0;
	int length = 0;

	string sub_s1 = s.substr(idx);

	Get_pi(sub_s1);

	for (n = 1; (idx + max_num + n - 1) < s.size(); n++) {
		string sub_s2 = s.substr(idx, max_num + n);

		bool check = Check_Two_Count_with_KMP(sub_s1, sub_s2);

		if (check == false)
			break;

		else {
			length = max_num + n;
		}
	}

	return length;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	int idx = 0;
	int max_num = 0;

	while (true) {
		if (idx == s.size())
			break;

		max_num = max(max_num, Find_Longest(max_num, idx));
		result = max(result, max_num);
		idx++;
	}

	cout << result;
}