#include <iostream>
#include <algorithm>
using namespace std;

int main() 
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n;
    cin >> n;
    pair<int, int> v[1000001];
    int x,y;
    for(int i = 0; i < n; i++) {
        cin >> x >> y;
        v[i] = {x, y};
    }
    
    sort(v, v+n);
    int left = v[0].first;
    int right = v[0].second;
    int res = 0;
    
    for(int i = 0; i < n-1; i++) {
        pair<int, int> p = v[i];
        if(p.first <= right) {
            right = max(right, p.second);
        } 
        else {
            res += (right - left);
            left = p.first;
            right = p.second;
        }
    }
    
    if(v[n-1].first <= right) {
        right = max(right, v[n-1].second);
        res += (right - left);
    }
    else {
        res += (right - left);
        res += (v[n-1].second - v[n-1].first);
    }
    
    cout << res;
}