#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<cstring>

using namespace std;

int n;
map<string, int>m; // {차량 번호 : 들어간 순서}
int* output;

void init()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		m[s] = i;
	}

	output = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int idx = m[s];
		output[i] = idx;
	}
}

// 추월 계산
// map의 value(들어간 순서) 와 비교하여 
// i번째 차의 나온 순서(output)를 
// i+1 번째~n-1번째 차의 나온 순서와 비교 (i>=0)
// 더 큰 경우 하나라도 있으면 i번째 차는 추월한 것

int overtake()
{
	int result = 0;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (output[i] > output[j]) {
				result++;
				break;
			}
		}
	}

	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	cout << overtake();
}