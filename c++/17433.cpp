#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cstdlib>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while(t--) {
        int n;
        vector<int> vec;
        cin >> n;
        vec.resize(n);
        for(int i = 0; i < n; i++) 
            cin >> vec[i];
            
        bool chk = true;
        for(int i = 1; i < n; i++)
            if(vec[0] != vec[i]) {
                chk = false;
                break;
            }
        
        if(chk) {
            cout << "INFINITY\n";
            continue;
        }
        
        sort(vec.begin(), vec.end());
        for(int i = 1; i < n; i++)
            vec[i-1] = vec[i] - vec[i-1];
        int m = vec[0];
        for(int i = 1; i < n - 1; i++)
            m = gcd(m, vec[i]);
        cout << m << '\n';
    }
}