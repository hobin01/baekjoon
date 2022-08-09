#include <iostream>

using namespace std;

int N;
double x1, y1;
double x2, y2;
double x3, y3;
double x4, y4;
double x, y;

void init()
{
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
}

void calc()
{
    // 직선 방향 벡터 구해서 방향 다르면 교점 존재
    // 방향 같으면 교점 없거나 무한
    
    pair<double, double> a = {x2 - x1, y2 - y1};
    pair<double, double> b = {x4 - x3, y4 - y3};
    // a != (0,0), b != (0,0)
    
    // (a,b), (c,d) 외적 : ad-bc
    if(a.first * b.second - a.second * b.first != 0) {
        // 방향 다름 : 교점 존재
        if(a.first == 0 && a.second != 0 && b.first != 0 && b.second != 0){
            x = x1;
            // (u, v) 방향 벡터 : (x - x1) / u = (y - y1) / v : 직선
            y = ((x - x3) / b.first) * b.second + y3;
        }
        else if(a.first == 0 && a.second != 0 && b.first != 0 && b.second == 0) {
            x = x1;
            y = y3;
        }
        else if(a.first != 0 && a.second == 0 && b.first != 0 && b.second != 0) {
            y = y1;
            x = ((y - y3) / b.second) * b.first + x3;
        }
        else if(a.first != 0 && a.second == 0 && b.first == 0 && b.second != 0) {
            x = x3;
            y = y1;
        }
        else if(a.first != 0 && a.second != 0 && b.first == 0 && b.second != 0) {
            x = x3;
            y = ((x - x1) / a.first) * a.second + y1;
        }
        else if(a.first != 0 && a.second != 0 && b.first != 0 && b.second == 0) {
            y = y3;
            x = ((y - y1) / a.second) * a.first + x1;
        }
        else if(a.first != 0 && a.second != 0 && b.first != 0 && b.second != 0) {
            // 직선 : y = px + q 
            double p1 = a.second / a.first;
            double q1 = y1 - p1 * x1;
            double p2 = b.second / b.first;
            double q2 = y3 - p2 * x3;
            x = (-1) * (q1 - q2) / (p1 - p2);
            y = p1 * ((-1) * (q1 - q2) / (p1 - p2)) + q1;
        }
        
        printf("POINT %.2f %.2f\n", x, y);
    }
    else {
        // 방향 같음 : 평행 or 일치 직선 
        
        // 일치 직선
        // (x3, y3), (x1, y1) 사이의 직선의 방향 벡터랑 기존 방향 벡터랑 방향 일치
        pair<double, double> c = {x3 - x1, y3 - y1};
        if(a.first * c.second - a.second * c.first == 0) {
            printf("LINE\n");
        }
        else{
            printf("NONE\n");
        }
    }
}

int main()
{
    cin >> N;
    while(N--){
        init();
        calc();
    }
}