#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>

using namespace std;

int T, n;
bool check[100000];
bool finish[100000];
int res;
vector<int>student;

void find(int idx)
{
	check[idx] = true;
	int next = student[idx];
	if (check[next] == false)
		find(next);
	else
	{
		if (finish[next] == false)
		{
			while (1)
			{
				res++;
				if (next == idx)
					break;
				next = student[next];
			}
		}
	}
	finish[idx] = true;
}

int main()
{
	cin >> T;
	while (T--)
	{
		cin >> n;
		res = 0;
		memset(check, false, sizeof(check));
		memset(finish, false, sizeof(finish));

		for (int i = 0; i < n; i++)
		{
			int partner;
			cin >> partner;
			student.push_back(partner - 1);
		}

		for (int i = 0; i < n; i++)
			if (check[i] == false)
				find(i);
		cout << n - res << '\n';
		student.clear();
	}
}