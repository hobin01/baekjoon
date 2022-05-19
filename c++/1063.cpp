#include <iostream>
#include <vector>
#include <string>

using namespace std;

int dy[8] = { 0,0,-1,1,1,1,-1,-1 };
int dx[8] = { 1,-1,0,0,1,-1,1,-1 };
// R, L, B, T, RT, LT, RB, LB 순

int chess[9][9]; // 아무것도 없으면 0, 돌 1, 왕 2
pair<int, int>king;
pair<int, int>rock;
int N;
vector<int> order; // 움직이는 순서

void init()
{
	string s1, s2, s3;
	cin >> s1 >> s2 >> N;
	king = { s1[1] - '1', s1[0] - 'A' };
	rock = { s2[1] - '1', s2[0] - 'A' };

	for (int i = 0; i < N; i++) {
		cin >> s3;
		if (s3 == "R") {
			order.push_back(0);
		}
		else if (s3 == "L") {
			order.push_back(1);
		}
		else if (s3 == "B") {
			order.push_back(2);
		}
		else if (s3 == "T") {
			order.push_back(3);
		}
		else if (s3 == "RT") {
			order.push_back(4);
		}
		else if (s3 == "LT") {
			order.push_back(5);
		}
		else if (s3 == "RB") {
			order.push_back(6);
		}
		else if (s3 == "LB") {
			order.push_back(7);
		}
	}
}

int main()
{
	init();

	for (auto i : order) {
		int ny = king.first + dy[i];
		int nx = king.second + dx[i];

		if (ny < 0 || ny >= 8 || nx < 0 || nx >= 8)
			continue;

		if (ny == rock.first && nx == rock.second) {
			int rock_ny = rock.first + dy[i];
			int rock_nx = rock.second + dx[i];

			if (rock_ny < 0 || rock_ny >= 8 || rock_nx < 0 || rock_nx >= 8)
				continue;

			rock = { rock_ny, rock_nx };
			king = { ny, nx };
		}
		else {
			king = { ny, nx };
		}
	}

	printf("%c%c\n", king.second + 'A', king.first + '1'); 
	printf("%c%c", rock.second + 'A', rock.first + '1');
}