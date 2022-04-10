#include<iostream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int main()
{
	int n;
	int inf = 987654321;
	cin >> n;
	int** arr = (int**)malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++)
		arr[i] = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 0)
				arr[i][j] = inf;
		}

	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (arr[i][j] > arr[i][k] + arr[k][j])
					arr[i][j] = arr[i][k] + arr[k][j];
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			if (arr[i][j] != inf)
				cout << 1 << ' ';
			else
				cout << 0 << ' ';
		}
		cout << '\n';
	}
}