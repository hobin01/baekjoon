#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

int n;
int arr[500001];
int tmp[500001];
long long result = 0;

void init()
{
	cin >> n;

    int chk[1000001];
  
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		arr[i] = num;
        chk[num] = i;
	}

    // B에 입력된 값에 0부터 부여
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        int idx = chk[num];
        arr[idx] = i;
    }
}

void merge(int start, int last)
{
	int mid = (start + last) / 2;
	int i = start;
	int j = mid + 1;
	int k = start;
	int cnt = 0;

	while (i <= mid && j <= last) {
		// 왼쪽 배열의 값이 정렬될 때
		if (arr[i] <= arr[j]) {
			tmp[k++] = arr[i++];
			result += (long long)cnt;
		}
		// 오른쪽 배열의 값이 정렬될 때
		else {
			tmp[k++] = arr[j++];
			cnt++;
		}
	}

	// 남은 부분 중 오른쪽 배열의 값이 정렬될 때
	if (i > mid) {
		int s = j;
		while (s <= last) {
			tmp[k++] = arr[s++];
			cnt++;
		}
	}
	// 남은 부분 중 왼쪽 배열의 값이 정렬될 때
	else {
		int s = i;
		while (s <= mid) {
			tmp[k++] = arr[s++];
			result += (long long)cnt;
		}
	}

	for (int t = start; t <= last; t++)
		arr[t] = tmp[t];
}

void mergesort(int start, int last)
{
	if (start < last) {
		int mid = (start + last) / 2;
		mergesort(start, mid);
		mergesort(mid + 1, last);
		merge(start, last);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	mergesort(0, n - 1);
	cout << result;
}