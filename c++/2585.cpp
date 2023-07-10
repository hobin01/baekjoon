#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

int n, k;
int dist[1002][1002];
bool visited[1002];
int result = 987654321; // 대충 잡아도 최대 2000만

void init()
{
    cin >> n >> k;
    
    vector<pair<double, double>> points;
    points.resize(n+2);
    
    int last = n+1;
    points[0] = {0, 0};
    points[last] = {10000, 10000};
    
    for(int i = 1; i <= n; i++) {
        double x, y;
        cin >> x >> y;
        points[i] = {x, y};
    }
    
    memset(dist, 0, sizeof(dist));
    memset(visited, false, sizeof(visited));
    
    for(int i = 0; i < (n+2); i++) {
        for(int j = i; j < (n+2); j++) {
            if(i == j) {
                dist[i][j] = 0;
                continue;
            }
            
            double x1 = points[i].first;
            double y1 = points[i].second;
            double x2 = points[j].first;
            double y2 = points[j].second;
            
            double d = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
            int dd = (int)(ceil(d / 10.0));
            dist[i][j] = dd;
            dist[j][i] = dd;
        }
    }
}

// 한 번 거쳐 간 지점은 삼각형 만드므로 거리 무조건 더 큼
bool dfs(int node, int cnt, int fuel)
{
    if(fuel >= dist[node][n+1]) {
        return true;
    }
    
    if(cnt > k) {
        return false;
    }
    
    visited[node] = true;
    
    for(int i = 1; i <= (n+1); i++) {
        if(visited[i])
            continue;
        if(dist[node][i] > fuel)
            continue;
        
        if(dfs(i, cnt + 1, fuel))
            return true;
    }
    
    return false;
}

void calc()
{
    int min_fuel = 1;
    int max_fuel = 1415; // root 2 * 10000 / 10 to ceil
    while(min_fuel <= max_fuel) {
        int mid_fuel = (min_fuel + max_fuel) / 2;
        memset(visited, false, sizeof(visited));
        if(dfs(0, 0, mid_fuel)) {
            max_fuel = mid_fuel - 1;
        }
        else {
            min_fuel = mid_fuel + 1;
        }
    }
    
    cout << min_fuel;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    calc();
}