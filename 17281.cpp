#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>

using namespace std;

int n;
vector<int> game[50];
vector<vector<int>>idx;

void Permutation()
{
	vector<int> v = { 2,3,4,5,6,7,8,9 };
	vector<int>per;
	do {
		for (int i = 0; i < v.size(); i++)
		{
			per.push_back(v.at(i));
		}
		per.insert(per.begin() + 3, 1);
		idx.push_back(per);
		per.clear();
	} while (next_permutation(v.begin(), v.end()));
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		vector<int>v;
		for (int j = 0; j < 9; j++)
		{
			int k;
			cin >> k;
			v.push_back(k);
		}
		game[i] = v;
		v.clear();
	}

	Permutation();

	int result = 0;
	int out = 0;
	int inning = 0;
	int first = 0;
	int hitter = 0;
	int score = 0;

	for (int i = 0; i < idx.size(); i++)
	{
		vector<int>line_up = idx[i];
		first = 0;
		out = 0;
		inning = 0;
		hitter = 0;
		score = 0;
		int base[4] = { 0,0,0,0 };

		while (1)
		{
			if (out == 3)
			{
				inning += 1;
				out = 0;
				base[0] = 0;
				base[1] = 0;
				base[2] = 0;
			}

			if (inning == n)
			{
				result = max(result, base[3]);
				break;
			}

			if (first == 9)
				first = 0;

			hitter = line_up[first];
			score = game[inning][hitter - 1];

			if (score == 0)
			{
				out += 1;
				first += 1;
			}
			if (score == 1)
			{
				if (base[0] == 0 && base[1] == 0 && base[2] == 0)
				{
					base[0] = 1;
					first += 1;
				}
				else if (base[0] == 1 && base[1] == 0 && base[2] == 0)
				{
					base[1] = 1;
					base[0] = 1;
					first += 1;
				}
				else if (base[0] == 0 && base[1] == 1 && base[2] == 0)
				{
					base[2] = 1;
					base[1] = 0;
					base[0] = 1;
					first += 1;
				}
				else if (base[0] == 0 && base[1] == 0 && base[2] == 1)
				{
					base[2] = 0;
					base[1] = 0;
					base[0] = 1;
					base[3] += 1;
					first += 1;
				}
				else if (base[0] == 1 && base[1] == 1 && base[2] == 0)
				{
					base[2] = 1;
					base[1] = 1;
					base[0] = 1;
					first += 1;
				}
				else if (base[0] == 1 && base[1] == 0 && base[2] == 1)
				{
					base[2] = 0;
					base[1] = 1;
					base[0] = 1;
					base[3] += 1;
					first += 1;
				}
				else if (base[0] == 0 && base[1] == 1 && base[2] == 1)
				{
					base[2] = 1;
					base[1] = 0;
					base[0] = 1;
					base[3] += 1;
					first += 1;
				}
				else if (base[0] == 1 && base[1] == 1 && base[2] == 1)
				{
					base[2] = 1;
					base[1] = 1;
					base[0] = 1;
					base[3] += 1;
					first += 1;
				}
			}

			if (score == 2)
			{
				if (base[0] == 0 && base[1] == 0 && base[2] == 0)
				{
					base[1] = 1;
					first += 1;
				}
				else if (base[0] == 1 && base[1] == 0 && base[2] == 0)
				{
					base[2] = 1;
					base[1] = 1;
					base[0] = 0;
					first += 1;
				}
				else if (base[0] == 0 && base[1] == 1 && base[2] == 0)
				{
					base[3] += 1;
					base[1] = 1;
					first += 1;
				}
				else if (base[0] == 0 && base[1] == 0 && base[2] == 1)
				{
					base[3] += 1;
					base[2] = 0;
					base[1] = 1;
					first += 1;
				}
				else if (base[0] == 1 && base[1] == 1 && base[2] == 0)
				{
					base[3] += 1;
					base[2] = 1;
					base[1] = 1;
					base[0] = 0;
					first += 1;
				}
				else if (base[0] == 1 && base[1] == 0 && base[2] == 1)
				{
					base[3] += 1;
					base[2] = 1;
					base[1] = 1;
					base[0] = 0;
					first += 1;
				}
				else if (base[0] == 0 && base[1] == 1 && base[2] == 1)
				{
					base[3] += 2;
					base[2] = 0;
					base[1] = 1;
					base[0] = 0;
					first += 1;
				}
				else if (base[0] == 1 && base[1] == 1 && base[2] == 1)
				{
					base[3] += 2;
					base[2] = 1;
					base[1] = 1;
					base[0] = 0;
					first += 1;
				}
			}

			if (score == 3)
			{
				if (base[0] == 0 && base[1] == 0 && base[2] == 0)
				{
					base[2] = 1;
					first += 1;
				}
				else if (base[0] == 1 && base[1] == 0 && base[2] == 0)
				{
					base[3] += 1;
					base[2] = 1;
					base[0] = 0;
					first += 1;
				}
				else if (base[0] == 0 && base[1] == 1 && base[2] == 0)
				{
					base[3] += 1;
					base[2] = 1;
					base[1] = 0;
					first += 1;
				}
				else if (base[0] == 0 && base[1] == 0 && base[2] == 1)
				{
					base[3] += 1;
					first += 1;
				}
				else if (base[0] == 1 && base[1] == 1 && base[2] == 0)
				{
					base[3] += 2;
					base[2] = 1;
					base[1] = 0;
					base[0] = 0;
					first += 1;
				}
				else if (base[0] == 1 && base[1] == 0 && base[2] == 1)
				{
					base[3] += 2;
					base[2] = 1;
					base[1] = 0;
					base[0] = 0;
					first += 1;
				}
				else if (base[0] == 0 && base[1] == 1 && base[2] == 1)
				{
					base[3] += 2;
					base[2] = 1;
					base[1] = 0;
					base[0] = 0;
					first += 1;
				}
				else if (base[0] == 1 && base[1] == 1 && base[2] == 1)
				{
					base[3] += 3;
					base[2] = 1;
					base[1] = 0;
					base[0] = 0;
					first += 1;
				}
			}
			if (score == 4)
			{
				base[3] += (base[0] + base[1] + base[2] + 1);
				base[0] = 0;
				base[1] = 0;
				base[2] = 0;
				first += 1;
			}

		}
		line_up.clear();
	}
	cout << result;
}