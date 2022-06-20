#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

int n;
string s1, s2, s3;
string yes = "yes";
string no = "no";
string res = no;

bool dp[201][201];

void init()
{
	cin >> n;
	dp[0][0] = true;
}

void stringInput()
{
	for (int i = 0; i <= s1.size(); i++) {
		for (int j = 0; j <= s2.size(); j++) {
			dp[i][j] = false;
		}
	}
	dp[0][0] = true;
	res = no;
	cin >> s1 >> s2 >> s3;
}

void resultOutput(int num, string result)
{
	cout << "Data set " << num << ": " << result << '\n';
}

void calculate()
{
	for (int i = 1; i <= s1.size(); i++) {
		if (s1[i - 1] == s3[i - 1]) {
			dp[i][0] = dp[i - 1][0];
		}
		else {
			dp[i][0] = false;
		}
	}

	for (int i = 1; i <= s2.size(); i++) {
		if (s2[i - 1] == s3[i - 1]) {
			dp[0][i] = dp[0][i - 1];
		}
		else {
			dp[0][i] = false;
		}
	}

	for (int i = 1; i <= s1.size(); i++) {
		for (int j = 1; j <= s2.size(); j++) {
			if (s1[i - 1] != s3[i + j - 1] && s2[j - 1] != s3[i + j - 1])
				dp[i][j] = false;
			else if (s1[i - 1] == s3[i + j - 1] && s2[j - 1] != s3[i + j - 1])
				dp[i][j] = dp[i - 1][j];
			else if (s1[i - 1] != s3[i + j - 1] && s2[j - 1] == s3[i + j - 1])
				dp[i][j] = dp[i][j - 1];
			else
				dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	for (int i = 1; i <= n; i++) {
		stringInput();
		
		calculate();

		if (dp[s1.size()][s2.size()])
			res = yes;
		
		resultOutput(i, res);
	}
}