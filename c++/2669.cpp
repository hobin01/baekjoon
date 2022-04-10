#include <iostream>

using namespace std;

int main()
{
	int arr[101][101] = { 0 };

	struct point {
		int x1;
		int y1;
		int x2;
		int y2;
	};

	point points[4] = {};

	for (int i = 0; i < 4; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		points[i] = { x1, y1, x2, y2 };
	}

	for (int i = 0; i < 4; i++) {
		int dx = points[i].x2 - points[i].x1;
		int dy = points[i].y2 - points[i].y1; 

		for (int j = 0; j < dy; j++) {
			for (int k = 0; k < dx; k++) {
				arr[points[i].y1 + j][points[i].x1 + k] = 1;
			}
		}
	}

	int result = 0;

	for (int i = 1; i < 101; i++) {
		for (int j = 1; j < 101; j++) {
			if (arr[i][j] == 1)
				result++;
		}
	}

	cout << result;
}