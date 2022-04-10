#include<iostream>
#include<vector>
#include<string>
#include<bitset>
#include<algorithm>

using namespace std;

int n, k;
vector<string>words; // 단어들 모음
bool learn[26]; // 알파벳 순으로 배웠는지 유무
int result = 0;

void init()
{
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		words.push_back(s);
	}

	// a, t, i, n, c는 무조건 배워야함
	learn[0] = true;
	learn['t' - 'a'] = true;
	learn['i' - 'a'] = true;
	learn['n' - 'a'] = true;
	learn['c' - 'a'] = true;
}

// idx : 알파벳 위치, cnt : 배운 알파벳 개수
void dfs(int idx, int cnt)
{
	// k개의 글자를 다 배운 경우
	if (cnt == k) {
		int res = 0;
		for (int i = 0; i < n; i++) {
			string s = words[i];
			bool check = true;

			// 처음 4글자, 마지막 4글자는 고정
			for (int j = 4; j < s.size() - 4; j++) {
				int num = s[j] - 'a';

				// 안 배운 글자 존재하는 경우
				if (learn[num] == false) {
					check = false;
					break;
				}
			}

			if (check == true)
				res++;
		}
		result = max(result, res);
	}

	// 아직 다 안 배운 경우
	else {
		for (int i = idx; i < 26; i++) {
			if (learn[i] == false) {
				learn[i] = true;
				dfs(i, cnt + 1);
				learn[i] = false;
			}
		}
	}

	return;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	// a,n,t,i,c도 못배우는 경우
	if (k < 5) {
		cout << 0;
		return 0;
	}
	
	// a,n,t,i,c 를 제외한 k-5개 학습 시작
	k -= 5;
	dfs(0, 0);
	cout << result;
}