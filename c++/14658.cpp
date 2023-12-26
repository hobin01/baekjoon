#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int N, M, L, K;
vector<pair<int,int>> stars;

// 별똥별 위치 기준으로 꼭지점 되게 해서 LxL 박스 만들고
// 그 안에 나머지 별똥별 얼마나 들어가는지 체크 
// 꼭지점, 모서리도 포함

void init()
{
    cin >> N >> M >> L >> K;
    int x, y;
    for(int i = 0; i < K; i++) {
        cin >> x >> y;
        stars.push_back({x, y});
    }
}

bool check(int x, int y, int maxX, int minX, int maxY, int minY)
{
    return (x >= minX) && (x <= maxX) && (y >= minY) && (y <= maxY);
}

int calc(pair<int,int> p1, pair<int, int> p2)
{
    // p1, p2 : 별똥별 위치 
    // p1, p2 각 x, y 좌표를 기준으로 4분면 만들어서 체크 
    // 최대값 나오는 곳이 정답 
    // 그럼 그 위치에 LxL 놓으면 됨
    
    int X = p1.first;
    int Y = p2.second;

    int maxX, minX, maxY, minY;
    int res = 0;
    int x, y, tmp;
    
    // x,y
    // 좌상 
    maxX = X + L;
    minX = X;
    maxY = Y;
    minY = Y - L;
    
    tmp = 0;
    for(auto s : stars) {
        x = s.first;
        y = s.second;
        if(check(x, y, maxX, minX, maxY, minY))
            tmp++;
    }
    res = max(res, tmp);
    
    // 좌하 
    maxX = X + L;
    minX = X;
    maxY = Y + L;
    minY = Y;
    
    tmp = 0;
    for(auto s : stars) {
        x = s.first;
        y = s.second;
        if(check(x, y, maxX, minX, maxY, minY))
            tmp++;
    }
    res = max(res, tmp);
    
    // 우상 
    maxX = X;
    minX = X - L;
    maxY = Y;
    minY = Y - L;
    
    tmp = 0;
    for(auto s : stars) {
        x = s.first;
        y = s.second;
        if(check(x, y, maxX, minX, maxY, minY))
            tmp++;
    }
    res = max(res, tmp);
    
    // 우하 
    maxX = X;
    minX = X - L;
    maxY = Y + L;
    minY = Y;
    
    tmp = 0;
    for(auto s : stars) {
        x = s.first;
        y = s.second;
        if(check(x, y, maxX, minX, maxY, minY))
            tmp++;
    }
    res = max(res, tmp);
    
    return res;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    
    int result = 0;
    for(auto s1 : stars) {
        for(auto s2 : stars) {
            result = max(result, calc(s1, s2));
        }
    }
    
    cout << K - result;
}