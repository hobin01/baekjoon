#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	int T, N;

	cin >> T;
	while (T--)
	{
		cin >> N;

		vector<int>app(N);
		int highest;

		for (int i = 0; i < N; i++)
		{
			int a, b;
			cin >> a >> b;
			app[a - 1] = b;
		}
		
		highest = app[0];
		int res = 1;

		for (int i = 1; i < N; i++)
		{
			if (app[i] < highest) {
				highest = app[i];
				res++;
			}
		}

		cout << res << '\n';
		app.clear();
	}
}