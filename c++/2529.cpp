#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

int k;
vector<char>relation;
vector<int>min_vec;
vector<int>max_vec;

void init()
{
	cin >> k;
	for (int i = 0; i < k; i++) {
		char c;
		cin >> c;
		relation.push_back(c);
		min_vec.push_back(9);
		max_vec.push_back(0);
	}
	min_vec.push_back(9);
	max_vec.push_back(0);
}

bool compare_num(int num1, int num2, char c)
{
	// num1 'c' num2의 결과 리턴 
	if (c == '<') {
		if (num1 < num2)
			return true;
		else
			return false;
	}

	if (c == '>') {
		if (num1 > num2)
			return true;
		else
			return false;
	}
}

bool compare_vec(vector<int>& v, char c)
{
	// v는 부등호 만족하는 애들만 들어옴

	if (c == 'M') {
		// max값 비교
		// max_vec과 비교하고자 하는 v 들어감
		for (int i = 0; i <= k; i++) {
			if (max_vec[i] < v[i])
				return true;
			else if (max_vec[i] > v[i])
				return false;
			else
				continue;
		}
	}

	if (c == 'm') {
		// min 값 비교
		// min_vec과 비교하고자 하는 v 들어감
		for (int i = 0; i <= k; i++) {
			if (min_vec[i] > v[i])
				return true;
			else if (min_vec[i] < v[i])
				return false;
			else
				continue;
		}
	}

	// 똑같은 결과일 때
	return false;
}

void bfs(int start)
{
	queue<vector<int>>q;
	vector<int>v;
	v.push_back(start);
	q.push(v);

	while (!q.empty())
	{
		vector<int>vec = q.front();
		q.pop();

		if (vec.size() == (k + 1)) {
			bool max_check = compare_vec(vec, 'M');
			bool min_check = compare_vec(vec, 'm');

			if (max_check)
				max_vec = vec;
			if (min_check)
				min_vec = vec;
		}

		else {
			int last_num = vec[vec.size() - 1];
			vector<int>::iterator iter;

			for (int num = 0; num < 10; num++) {
				iter = find(vec.begin(), vec.end(), num);
				if (iter == vec.end()) {
					// num 없는 경우
					if (compare_num(last_num, num, relation[vec.size() - 1])) {
						vector<int> next_vec = vec;
						next_vec.push_back(num);
						q.push(next_vec);
					}
				}

			}
		}
	}
}

void print_vec(vector<int>& v)
{
	for (int i = 0; i < v.size(); i++) {
		cout << v[i];
	}
}

int main()
{
	init();
	for (int start_num = 0; start_num < 10; start_num++) {
		bfs(start_num);
	}

	print_vec(max_vec);
	cout << '\n';
	print_vec(min_vec);
}