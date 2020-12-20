#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
#include<string>

using namespace std;

int N, M;
int* apps;
int* Mem;
int dp[10001];
int res;

void make_input()
{
	cin >> N >> M;
	apps = (int*)malloc(sizeof(int) * N);
	Mem = (int*)malloc(sizeof(int) * N);
	for (int i = 0; i < N; i++)
		cin >> apps[i];
	for (int i = 0; i < N; i++)
		cin >> Mem[i];
	memset(dp, 0, sizeof(dp));
}

int main()
{
	make_input();
	for (int i = 0; i < N; i++)
		for (int j = 10000; j >= Mem[i]; j--)
			dp[j] = max(dp[j], (dp[j - Mem[i]] + apps[i]));

	for(int i=0;i<=10000;i++)
		if (dp[i] >= M)
		{
			res = i;
			break;
		}

	cout << res;
	
}