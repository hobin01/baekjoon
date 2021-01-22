#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;

int n;
vector<int>alkal;
vector<int>acid;
int res1, res2; // 작은 값, 큰 값

void make_v()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int num;
		cin >> num;
		if (num >= 0)
			acid.push_back(num);
		else
			alkal.push_back(num);
	}
	sort(acid.begin(), acid.end());
	sort(alkal.begin(), alkal.end());
}

pair<int, int> binary_search(vector<int>v, int num)
{
	// num이 v에 있으면 0 리턴 (중성) 
	// 없으면 마지막까지 찾은 index와 합 비교
	int start = 0;
	int last = v.size() - 1;
	int mid = (start + last) / 2;
	bool check = false;
	num = (-1) * num;

	while (last - start >= 0) {
		mid = (start + last) / 2;

		if (v[mid] == num) {
			check = true;
			break;
		}
		else if (v[mid] > num) {
			last = mid - 1;
		}
		else {
			start = mid + 1;
		}
	}

	if (check) {
		if (num >= 0)
			return { (-1) * num,num };
		else
			return { num,(-1) * num };
	}
	else {
		if (start == v.size()) {
			if (num >= 0) {
				return { (-1) * num,v[start - 1] }; //(-1)*num이 원래 수
			}
			else {
				return { v[start - 1],(-1) * num };
			}
		}
		else if (last == -1) {
			if (num >= 0) {
				return { (-1) * num, v[0] };
			}
			else {
				return { v[0],(-1) * num };
			}
		}
		else {
			int t1 = abs(num - v[start]);
			int t2 = abs(num - v[last]);

			if (t1 >= t2) {
				if (num >= 0) {
					return { (-1) * num, v[last] };
				}
				else {
					return { v[last],(-1) * num };
				}
			}
			else {
				if (num >= 0) {
					return { (-1) * num, v[start] };
				}
				else {
					return { v[start],(-1) * num };
				}
			}
		}
	}
}

void find()
{
	if (acid.empty()) {
		res1 = alkal[alkal.size() - 2];
		res2 = alkal[alkal.size() - 1];
	}
	else if (alkal.empty()) {
		res1 = acid[0];
		res2 = acid[1];
	}
	else if (acid.size() == 1) {
		pair<int, int>t1 = binary_search(alkal, acid[0]);
		res1 = t1.first;
		res2 = t1.second;
	}
	else if (alkal.size() == 1) {
		pair<int, int>t2 = binary_search(acid, alkal[0]);
		res1 = t2.first;
		res2 = t2.second;
	}
	else {
		pair<int, int>tmp1 = { alkal[alkal.size() - 2], alkal[alkal.size() - 1] };
		pair<int, int>tmp2 = { acid[0], acid[1] };

		if (alkal.size() >= acid.size()) {

			pair<int, int>result = { 1000000001,1000000001 };
			for (int i = 0; i < acid.size(); i++) {
				pair<int, int>tmp = binary_search(alkal, acid[i]);
				if (abs(result.first + result.second) > abs(tmp.first + tmp.second)) {
					result = tmp;
				}
			}
			res1 = result.first;
			res2 = result.second;
		}

		else {
			pair<int, int>result = { 1000000001,1000000001 };
			for (int i = 0; i < alkal.size(); i++) {
				pair<int, int>tmp = binary_search(acid, alkal[i]);
				if (abs(result.first + result.second) > abs(tmp.first + tmp.second)) {
					result = tmp;
				}
			}
			res1 = result.first;
			res2 = result.second;
		}

		if (abs(tmp1.first + tmp1.second) < abs(tmp2.first+tmp2.second)) {
			if (abs(tmp1.first + tmp1.second) < abs(res1 + res2)) {
				res1 = tmp1.first;
				res2 = tmp1.second;
			}
		}

		else {
			if (abs(tmp2.first + tmp2.second) < abs(res1 + res2)) {
				res1 = tmp2.first;
				res2 = tmp2.second;
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	make_v();
	find();
	cout << res1 << ' ' << res2;
}