#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int n;
vector<int>population;
vector<int>graph[11];
vector<vector<int>>comb[6]; // 10/2=5
bool check[11];
int result = 987654321;

void make_graph()
{
	cin >> n;
	population.push_back(0);
	for (int i = 1; i <= n; i++) {
		int num;
		cin >> num;
		population.push_back(num);
	}

	for (int i = 1; i <= n; i++) {
		int location;
		cin >> location;
		for (int j = 1; j <= location; j++) {
			int num;
			cin >> num;
			graph[i].push_back(num);
		}
	}

	memset(check, false, sizeof(check));
}

// nCr의 케이스 모두 구하기
void make_combinations(int r)
{
	vector<int>v;
	for (int i = 1; i <= n; i++)
		v.push_back(i);

	vector<int>ind;
	for (int i = 0; i < r; i++)
		ind.push_back(1);
	for (int i = 0; i < n - r; i++)
		ind.push_back(0);
	sort(ind.begin(), ind.end());

	do {
		vector<int>tmp;
		for (int i = 0; i < ind.size(); i++) {
			if (ind[i] == 1)
				tmp.push_back(v[i]);
		}
		comb[r].push_back(tmp);
		tmp.clear();
	} while (next_permutation(ind.begin(), ind.end()));
}

// v에 있는 애들이 다 연결되었는지 확인
bool possible(vector<int>v)
{
	memset(check, false, sizeof(check));
	queue<int>q;
	q.push(v[0]);
	int cnt = 0;

	while (!q.empty())
	{
		int now = q.front();
		check[now] = true;
		cnt++;
		q.pop();

		for (int i = 0; i < graph[now].size(); i++) {
			int next = graph[now][i];
			vector<int>::iterator iter;

			iter = find(v.begin(), v.end(), next);
			if (iter != v.end()) {
				if (check[next] == false) {
					q.push(next);
					check[next] = true;
				}
			}
		}
	}

	if (cnt == v.size())
		return true;
	else
		return false;
}

// v 원소 말고 나머지 애들 구하기
vector<int> others(vector<int>v)
{
	vector<int>other_vec;
	bool other[11];
	memset(other, true, sizeof(other));

	for (int i = 0; i < v.size(); i++) {
		other[v[i]] = false;
	}

	for (int i = 1; i <= n; i++) {
		if (other[i] == true)
			other_vec.push_back(i);
	}

	return other_vec;
}

// v에 있는 애들 합 구하기
int peoples(vector<int>v)
{
	int sum = 0;
	for (int i = 0; i < v.size(); i++) {
		sum += population[v[i]];
	}
	return sum;
}

void calculate(vector<int>v)
{
	vector<int>v2 = others(v);
	if (possible(v) == true) {
		if (possible(v2) == true) {
			int sum1 = peoples(v);
			int sum2 = peoples(v2);
			if (result > abs(sum1 - sum2)) {
				result = abs(sum1 - sum2);
			}
		}
	}
}

int main()
{
	make_graph();
	for (int r = 1; r <= n / 2; r++)
		make_combinations(r);

	for (int r = 1; r <= n / 2; r++) {
		for (int t = 0; t < comb[r].size(); t++) {
			calculate(comb[r][t]);
		}
	}

	if (result == 987654321)
		cout << -1;
	else
		cout << result;
}