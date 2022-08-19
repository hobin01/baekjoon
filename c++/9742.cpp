#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string s = "";
int n = 0;
int max_num = 0;

void init()
{
    int s_size = s.size();
    max_num = 1;
    
    for(int i = 1; i <= s_size; i++) {
        max_num *= i;
    }
}

void calc()
{
    int idx = 0;
    string ss = s;
    do{
        idx++;
        if(idx == n){
            cout << ss << ' ' << n << " = " << s << '\n';
            return;
        }
    }while(next_permutation(s.begin(), s.end()));
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    while(cin >> s >> n) {
        init();
        if(max_num < n)
            cout << s << ' ' << n << " = " << "No permutation\n";
        
        else
            calc();
        
    }
}