#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int h, w;
int* block;
bool Left, Right;
int res = 0;

int main()
{
	cin >> h >> w;
	block = (int*)malloc(sizeof(int) * w);
	for (int i = 0; i < w; i++)
	{
		int height;
		cin >> height;
		block[i] = height;
	}

	for (int i = 1; i < (w - 1); i++) {

		for (int j = h - block[i]; j > 0; j--) {

			Left = false;
			for (int k = 0; k < i; k++) {
				if (block[k] >= block[i] + j) {
					Left = true;
					break;
				}
			}

			Right = false;
			for (int k = (i + 1); k < w; k++) {
				if (block[k] >= block[i] + j) {
					Right = true;
					break;
				}
			}

			if (Left && Right) {
				res += j;
				break;
			}
		}
	}

	cout << res;
}