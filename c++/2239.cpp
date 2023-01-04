#include<iostream>
#include<vector>
#include<string>
using namespace std;

int sudoku[10][10]; // 원래 맵
bool row[10][10]; // 각 행 별로 숫자 체크용
bool column[10][10]; // 각 열 별로 숫자 체크용
bool square[10][10]; // 각 3x3 별로 숫자 체크용

int three_square(int y, int x)
{
	return (y / 3) * 3 + x / 3;
}

void init()
{
  for (int i = 0; i < 9; i++) {
    string s;
    cin >> s;
    for(int j = 0; j < 9; j++) {
      sudoku[i][j] = s[j] - '0';
      if (sudoku[i][j]) {
				column[j][sudoku[i][j]] = true;
				row[i][sudoku[i][j]] = true;
				square[three_square(i, j)][sudoku[i][j]] = true;
			}
    }
	}
}

void printSudoku()
{
  for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
			cout << sudoku[i][j];
		cout << endl;
	}
}

void dfs(int count)
{
	if (count == 81) {
    // 1~9 순으로 백트래킹하므로
    // 가장 먼저 수도쿠 완료되면 정답 
		printSudoku();
		exit(0);
	}
  
	int y = count / 9;
	int x = count % 9;

	if (sudoku[y][x])
		dfs(count + 1);
	else {
		for (int k = 1; k <= 9; k++) {
			if (!column[x][k] && !row[y][k] && !square[three_square(y, x)][k]) {
				sudoku[y][x] = k;
				column[x][k] = true;
				row[y][k] = true;
				square[three_square(y, x)][k] = true;
				dfs(count + 1);
				sudoku[y][x] = 0;
				column[x][k] = false;
				row[y][k] = false;
				square[three_square(y, x)][k] = false;
			}
		}
	}
}
int main()
{
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
	
  init();
  dfs(0);
}