#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int m;
int Q;
int n, x;
int f[200001];
// 2^18 < 500,000 < 2^19
#define max_log 20
int table[21][200001]; // table[y][x] : x에서 시작해 2^y 이동한 위치


// Q<=200,000, n<=500,000 이므로
// log n 에 완료해야함
// 주어진 n의 최댓값 500,000의 log값을 k라 하면
// n & 1<<k, k-- 를 반복하면서 해당 비트 나오면 
// 해당 비트의 f값으로 업데이트
// ex) f_15(x) = f_8( f_4 ( f_2 ( f_1(x) ) ) ) )
// 합성함수 1번을 이동 1번이라 하자.

// 기본 그래프 + 전처리
void init()
{
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int num;
		cin >> num;
		f[i] = num;
	}

	// table[0][x] = f(x)
	for (int i = 1; i <= m; i++)
		table[0][i] = f[i];

	// table[y][x] : x에서 시작해 2^y 이동한 위치
	// 이는 x에서 시작해 2^(y-1) 이동한 위치에서 2^(y-1) 이동한 것과 같음
	for (int i = 1; i < max_log; i++) {
		for (int j = 1; j <= m; j++) {
			int tmp = table[i - 1][j];
			table[i][j] = table[i - 1][tmp];
		}
	}
}

// 15 = 8+4+2+1 을 생각하면
// 15번 이동 = 1번 이동 후 2번 이동 후 4번 이동 후 8번 이동 한 것과 같음
// 이를 이용한 것
int solve(int n, int x)
{
	int cur = x; // 시작점
	for (int k = 0; k < max_log; k++) {
		if (n & (1 << k)) {
			cur = table[k][cur];
		}
	}
	return cur;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();

	cin >> Q;
	while (Q--) {
		cin >> n >> x;
		
		int res = solve(n, x);
		cout << res << '\n';
	}
}