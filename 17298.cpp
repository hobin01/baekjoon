#include<iostream>
#include<algorithm>
#include<stack>
#include<vector>

using namespace std;

int main() 
{
	int n;
	cin >> n;
	stack<int>st;
	vector<int>v;
	vector<int>res(n, -1);

	if (n == 1) {
		int num;
		cin >> num;
		printf("-1");
		return 0;
	}
	
	while (n--) {
		int num;
		cin >> num;
		v.push_back(num);
	}

	for (int i = 0; i < n; i++) {
		while (!st.empty() && (v[st.top()] < v[i])) {
			res[st.top()] = v[i];
			st.pop();
		}
		st.push(i);
	}

	for (int i = 0; i < n; i++)
		printf("%d ", res[i]);
}
