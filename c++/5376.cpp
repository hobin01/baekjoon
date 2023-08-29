#include <iostream>
#include <string>

using namespace std;

int t;
string s;
string cycle;
string non;
long long p; // 분자
long long q; // 분모 

void init()
{
    s = "";
    cycle = "";
    non = "";
    p = 1;
    q = 1;
}

void parse()
{
    for(int i = 2; i < s.size(); i++) {
        if(s[i] == '(') {
            cycle = s.substr(i+1, s.size());
            cycle = cycle.substr(0, cycle.size() - 1);
            non = s.substr(2, i-2);
            return;
        }
    }
    
    // 사이클 없는 경우 
    cycle = "";
    non = s.substr(2, s.size());
}

long long gcd(long long a, long long b) 
{
    return b ? gcd(b, a%b) : a;    
}

void calc()
{
    // 사이클 없는 경우 
    if(cycle.size() == 0) {
        for(int i = 0; i < s.size() - 2; i++) {
            q *= 10;
        }
        p = stoll(non);
        
        long long r = gcd(p, q);
        q /= r;
        p /= r;
    }
    
    else {
        for(int i = 0; i < cycle.size(); i++) {
            q *= 10;
        }
        q--; 
        
        for(int i = 0; i < non.size(); i++) {
            q *= 10;
        }
        
        if(non.size() == 0) {
            p = stoll(cycle);
        }
        else {
            string tmp = non + cycle;
            p = stoll(tmp) - stoll(non);
        }
        
        long long r = gcd(p, q);
        q /= r;
        p /= r;
    }
    
    cout << p << "/" << q << '\n';
}

int main()
{   
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> t;
    while(t--) {
        init();
        cin >> s;
        
        parse();
        calc();
    }
}