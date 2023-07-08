#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    vector<int> vec;
    cin >> n;
    vec.resize(n);
    for(int i = 0; i < n; i++) 
        cin >> vec[i];
    
    sort(vec.begin(), vec.end());
    for(int i = 1; i < n; i++)
        vec[i-1] = vec[i] - vec[i-1];
    int m = vec[0];
    for(int i = 1; i < n - 1; i++)
        m = gcd(m, vec[i]);
    cout << m;
}