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
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		arr[i] = num;
	}
}

// 버블 소트의 swap 개수 
// = merge 소트에서 merge과정에서의 교차점 개수
// 오름차순 정렬 기준으로
// 왼쪽 배열의 값이 tmp에 정렬될 때마다 cnt 더해줌
// 오른쪽 배열의 값이 tmp에 정렬될 때마다 cnt+1
// (오른쪽 배열의 값이 정렬된다는 것은 해당 값 이전의 오른쪽 배열 값은
// 이미 정렬된 상황이므로 교차점이 이전 오른쪽 배열의 값에 +1 한 것과 같음)

// 합병, 교차점도 함께 구하기
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

