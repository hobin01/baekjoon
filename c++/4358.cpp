#include <iostream>
#include <map>
#include <string>

using namespace std;

void roundNum(int cnt, int total, string s)
{
    double ret = ((double)(cnt) / (double)(total)) * 100;
    
    cout << fixed;
    cout.precision(4);
    cout << s << ' ' << ret << '\n';
}

int main()
{
    
    string s;
    map<string, int> m;
    int total = 0;

    while(getline(cin, s)) {
        if(m.find(s) == m.end())
            m[s] = 1;
        else
            m[s]++;
        total++;
    }
    
    for(auto c : m) {
        roundNum(c.second, total, c.first);
    }
}