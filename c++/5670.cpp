#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n;
string s;
vector<int> result;
vector<string> vec;

class Trie {
	Trie* ch[27]; // 현재 알파벳에 대한 트라이 (마지막은 .)

public:
	Trie() {
		for(int i = 0; i < 27; i++) {
			ch[i] = NULL;
		}
	}

public:
	~Trie() {
		for(int i = 0; i < 27; i++) {
			if(ch[i] != NULL)
				delete ch[i];
		}
	}
	
public:
	void insert(const char* s) {
		// 문자 마지막 (.)
		if(*s == '.') {
			if(this->ch[26] == NULL)
				this->ch[26] = new Trie;
			this->ch[26]->insert(s+1);
			return;
		} 
		
		// 끝 도달 
		if(*s == 0) {	
			return;
		}
		
		int now = *s - 'a';
		
		if(ch[now] == NULL) {
			ch[now] = new Trie;
		}
		
		this->ch[now]->insert(s+1);
	}

public:
	void calc(const char* s, int res) {
		if(*s == 0) {
			result.push_back(res);
			return;
		}
		
		int now;
		if(*s != '.')
			now = *s - 'a';
		else 
			now = 26;
		
		int cnt = 0;
		if(now != 26) {
			for(int i = 0; i < 27; i++) {
				if(this->ch[now]->ch[i] != NULL)
					cnt++;
				if(cnt == 2)
					break;
			}
		}
		
		// 브랜치 생성 
		if(cnt == 2) {
			// . 아닌 경우 
			if(*(s+1) != '.') 
				this->ch[now]->calc(s+1, res+1);
			else 
				this->ch[now]->calc(s+1, res);
		}
		else {
			this->ch[now]->calc(s+1, res);
		}
	}
};

void init(Trie* trie)
{
	result.clear();
	vec.clear();
	
	for(int i = 0; i < n; i++) {
		cin >> s;
		s += '.';
		vec.push_back(s);
		trie->insert(s.c_str());
	}
}

void game(Trie* trie)
{
	for(auto v : vec) {
		trie->calc(v.c_str(), 1);
	}
	
	double res = 0;
	for(auto r : result) {
		res += (double)r;
	}
	
	printf("%.2f\n", res / (double)n);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	Trie* trie;
	while(cin >> n) {
		trie = new Trie;
		init(trie);
		game(trie);
		delete trie;
	}
}