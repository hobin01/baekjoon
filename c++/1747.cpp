#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>

using namespace std;

int n;
int Max = 1003002;
bool arr[1003002]; //1,000,000 이상 소수 중 가장 작은 펠린드롬수

void prime()
{
	//에라토스테네스
	memset(arr, true, sizeof(arr));
	arr[0] = false;
	arr[1] = false;
	int Max = 1003002;
	int half = int(sqrt(Max)) + 1;
	for (int i = 2; i < half; i++) {
		if (arr[i] == false)
			continue;
		for (int j = i * 2; j < Max; j += i) {
			arr[j] = false;
		}
	}
}

bool palindrome(int num)
{
	string str = to_string(num);
	int size = str.size();
	for (int i = 0; i <= size / 2; i++) {
		if (str[i] != str[size - i - 1]) {
			return false;
			break;
		}
	}
	return true;
}

int main()
{
	int result = Max;
	cin >> n;
	prime();
	for (int i = n; i < Max; i++) {
		if (arr[i] && palindrome(i)) {
			result = i;
			break;
		}
	}
	cout << result;
}