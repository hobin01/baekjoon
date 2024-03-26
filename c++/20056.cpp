#include <iostream>
#include <vector>

using namespace std;

int N, M, K;
struct ball {
	int m; // 질량 
	int s; // 속력  
	int d; // 방향  
};

int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1}; // 0~7 방향 

vector<ball> vec[50][50];
vector<ball> tmp[50][50]; // 게임 진행할 때 사용할 용도 

void init()
{
	cin >> N >> M >> K;
	
	int r, c, m, s, d;
	for(int i = 0; i < M; i++) {
		cin >> r >> c >> m >> s >> d;
		r--;
		c--;
		ball b = {m, s, d};
		vec[r][c].push_back(b);
	}
} 

void clear_vec_arr(vector<ball> v[50][50]) 
{
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			v[i][j].clear();
		}
	}	
}

void swap_vec_arr()
{
	clear_vec_arr(tmp);
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			tmp[i][j] = vec[i][j];
		}
	}
	clear_vec_arr(vec);
}

void move_balls()
{
	// tmp에 있는 ball 기준으로 볼 움직이기 
	swap_vec_arr();
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			for(auto b : tmp[i][j]) {
				int ny = (i + dy[b.d] * b.s) % N;
				int nx = (j + dx[b.d] * b.s) % N;
				if(ny < 0) {
					ny += N;
				}
				if(nx < 0) {
					nx += N;
				}
				vec[ny][nx].push_back(b);
			}
		}
	}
}

void split_balls()
{
	// vec에 있는 ball 기준으로 분해하기 
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if(vec[i][j].size() < 2)
				continue;
			
			int size = vec[i][j].size();
			int nm = 0;
			int ns = 0;
			bool nd = false; // 다 같으면 true, 아니면 false
			int cnt = 0; // 홀수 카운트용 
			
			for(auto b : vec[i][j]) {
				nm += b.m;
				ns += b.s;
				cnt += (b.d % 2);
			}
			if(cnt == 0 || cnt == size)
				nd = true;
			
			// 있던 애들 제거 
			vec[i][j].clear();
			
			// 4개로 나누기 
			nm = (nm / 5);
			
			// 질량 0되면 소멸 
			if(nm == 0)
				continue;
				
			ns = (ns / size);
			for(int k = 0; k < 8; k+=2) {
				ball nb = {nm, ns, k};
				if(nd == false) {
					nb.d++;
				}
				vec[i][j].push_back(nb);
			}
		}
	} 
}

void game()
{
	while(K--) {
		move_balls();
		split_balls();	
	}
	
	int result = 0;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			for(auto b : vec[i][j]) {
				result += b.m;
			}
		}
	}
	
	cout << result;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	
	init();
	game();
}