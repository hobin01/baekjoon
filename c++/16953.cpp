#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

string doubling(string s) {
	// s를 2배 시키기
	int num = stoi(s);
	num *= 2;
	return to_string(num);
}

string Add(string s) {
	return s + "1";
}

int check(string s1, string s2) {
	// s1 < s2 : 0 => 가능성 있음
	// s1 == s2 : 1 => 정답
	// s1 > s2 : 2 => 진행 안 해도 됨
	if (s1 == s2) {
		return 1;
	}
	else {
		if (s1.size() == s2.size()) {
			if (s1 > s2)
				return 2;
			else
				return 0;
		}
		else if (s1.size() > s2.size()) {
			return 2;
		}
		else if (s1.size() < s2.size()) {
			return 0;
		}
	}
}

int main() {
	
	//  bfs로 비교
	//  비교하다가 제일 먼저 일치하는 순간 나오면 정답
	//  끝까지 없으면 실패

	string a, b;
	cin >> a >> b;

	int result = 0;

	queue< pair<string, int> >q;
	q.push({ a, 0 });

	while (!q.empty()) {
		string s = q.front().first;
		int r = q.front().second;

		q.pop();

		int ret = check(s, b);
		if (ret == 1) {
			result = r;
			break;
		}

		if (ret == 2)
			continue;

		string s2 = doubling(s);
		string s3 = Add(s);

		q.push({ s2, r + 1 });
		q.push({ s3, r + 1 });
	}

	if (result == 0)
		cout << -1;
	else 
		cout << result + 1;
}