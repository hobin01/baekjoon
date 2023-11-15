#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int hello, world, sum;
int N;

void init()
{
    cin >> N;
    hello = 0;
    world = 0;
    sum = 0;
}

void calc(vector<int> &vec)
{
    // h, w != 0 
    int d = vec[0];
    int e = vec[1];
    int h = vec[2];
    int l = vec[3];
    int o = vec[4];
    int r = vec[5];
    int w = vec[6];
        
    if((h == 0) || (w == 0))
        return;
        
    hello = h * 10000 + e * 1000 + l * 110 + o;
    world = w * 10000 + o * 1000 + r * 100 + l * 10 + d;
    sum = hello + world;
        
    if(sum == N)
        return;
        
    // 초기화 (No answer 체크용)
    hello = 0;
    world = 0;
    sum = 0;
}

void perm()
{
    vector<int> v = {0,1,2,3,4,5,6,7,8,9};
    vector<int> tmp;
    
    tmp.resize(7);
    
    do {
        for(int i = 0; i < 7; i++) {
            tmp[i] = v[i];
        }
        
        calc(tmp);
        if(sum != 0)
            return;
        
        tmp.clear();
        tmp.resize(7);
        reverse(v.begin() + 7, v.end());
    }while(next_permutation(v.begin(), v.end()));
}

void no_result()
{
    cout << "No Answer";
}

void yes_result(string &s1, string &s2, string &s3)
{
    cout << "  " << s1 << '\n';
    cout << "+ " << s2 << '\n';
    cout << "-------" << '\n';
    if(s3.size() == 5) 
        cout << "  " << s3;
    else 
        cout << " " << s3;
}

void get_result()
{
    if(sum == 0) {
        no_result();
    }
    else {
        string s1 = to_string(hello);
        string s2 = to_string(world);
        string s3 = to_string(sum);
        yes_result(s1, s2, s3);
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    perm();
    get_result();
}