#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

vector<pair<long long, long long>>box1, box2;
vector<string>result;
string res;


void make_box()
{
	long long x1, y1;
	long long x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	box1.push_back({ x1,y1 });
	box1.push_back({ x2,y2 });

	cin >> x1 >> y1 >> x2 >> y2;
	box2.push_back({ x1,y1 });
	box2.push_back({ x2,y2 });

	result.push_back("POINT");
	result.push_back("LINE");
	result.push_back("FACE");
	result.push_back("NULL");
}

string solve(vector<pair<long long,long long>>v1,vector<pair<long long,long long>>v2)
{
	if (v1[0].first == v2[1].first || v1[1].first == v2[0].first)
	{
		if (v1[0].second == v2[1].second || v1[1].second == v2[0].second)
			return result[0];
		else if ((abs(v1[1].second - v1[0].second) + abs(v2[1].second - v2[0].second)) > max(abs(v1[1].second - v2[0].second), abs(v1[0].second - v2[1].second)))
		{
			return result[1];
		}
		else
			return result[3];
	}
	else if ((abs(v1[0].first - v1[1].first) + abs(v2[0].first - v2[1].first)) > max(abs(v1[0].first - v2[1].first), abs(v1[1].first - v2[0].first)))
	{
		if (v1[0].second == v2[1].second || v1[1].second == v2[0].second)
			return result[1];
		else if ((abs(v1[1].second - v1[0].second) + abs(v2[1].second - v2[0].second)) > max(abs(v1[0].second - v2[1].second), abs(v1[1].second - v2[0].second)))
			return result[2];
		else
			return result[3];
	}
	else
		return result[3];
}

int main()
{
	make_box();
	res = solve(box1, box2);
	cout << res;
}