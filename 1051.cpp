#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	int n, m;
	int res = 1;
	char arr[50][50];

	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		for (int j = 0; j < m; j++)
			arr[i][j] = s[j];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) {
			char c = arr[i][j];
			for (int k = 0; k < n; k++) {
				char tmp = arr[k][j];
				if (i == k)
					continue;
				if (c == tmp) {
					int dist = abs(i - k);
					if ((j + dist) >= 0 && (j + dist) < m) {
						if (tmp == arr[k][j + dist])
							if (c == arr[i][j + dist])
								res = max(res, (dist+1) * (dist+1));
					}
					if ((j - dist) >= 0 && (j - dist) < m) {
						if (tmp == arr[k][j - dist])
							if (c == arr[i][j - dist])
								res = max(res, (dist+1) * (dist+1));
					}
				}
			}
		}
	}

	cout << res;
}