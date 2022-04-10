#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	int n, m;
	string str;
	cin >> n >> m;
	cin >> str;
	
	int res = 0;
	int cnt = 0;
	for (int i = 0; i < (m-2); i++)
	{
		if (str[i] == 'I' && str[i + 1] == 'O' && str[i + 2] == 'I')
		{
			cnt++;
			if (cnt == n)
			{
				res++;
				cnt--;
			}
			i++;
		}
		else
			cnt = 0;
	}
	cout << res;
}