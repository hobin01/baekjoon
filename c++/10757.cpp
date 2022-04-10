#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

string add(string a, string b) {
	string result = "";

	if (a.size() != b.size()) {
		string zeros = "";

		if (a.size() < b.size()) {
			for (int i = 0; i < (b.size() - a.size()); i++)
				zeros += '0';
			a.insert(0, zeros);
		}

		else {
			for (int i = 0; i < (a.size() - b.size()); i++)
				zeros += '0';
			b.insert(0, zeros);
		}
	}

	int size = a.size();
	int tmp = 0;
	for (int i = size - 1; i > 0; i--) {
		int x = a[i] - '0';
		int y = b[i] - '0';
		if (x + y + tmp >= 10) {
			result += (char)('0' + (x + y + tmp - 10));
			tmp = 1;
		}
		else {
			result += (char)('0' + (x + y + tmp));
			tmp = 0;
		}
	}

	int last = (a[0] - '0') + (b[0] - '0') + tmp;
	string last_s = to_string(last);
	reverse(last_s.begin(), last_s.end());
	result += last_s;
	reverse(result.begin(), result.end());

	return result;
}

int main()
{
	string a, b;
	cin >> a >> b;
	cout << add(a, b);
}