#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N;
double x, y;

struct Point {
    double x;
    double y;
};

struct Circle {
    Point p;
    double r;
};

vector<Point> points;
double eps = 1e-9;

void init() {
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> x >> y;
        points.push_back({x, y});
    }
}

double dist(Point &p1, Point &p2) {
    double d = 0;
    d += (p1.x - p2.x) * (p1.x - p2.x);
    d += (p1.y - p2.y) * (p1.y - p2.y);
    return sqrt(d);
}

Circle circleFromTwoPoints(Point &p1, Point &p2) {
    Circle c;
    c.p.x = (p1.x + p2.x) / 2;
    c.p.y = (p1.y + p2.y) / 2;
    c.r = dist(p1, p2) / 2;
    return c;
}

Circle circleFromThreePoints(Point &p1, Point &p2, Point &p3) {
    // (x - x1)^2 + (y - y1)^2 = (x - x2)^2 + (y - y2)^2 = (x - x3)^2 + (y - y3)^2
    // 위 식 이용해서 행렬식 구하면 외심 구할 수 있음 
    double det = 2 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
    double x = (p1.x * p1.x + p1.y * p1.y) * (p2.y - p3.y) 
             + (p2.x * p2.x + p2.y * p2.y) * (p3.y - p1.y)
             + (p3.x * p3.x + p3.y * p3.y) * (p1.y - p2.y);
    x /= det;
    double y = (p1.x * p1.x + p1.y * p1.y) * (p3.x - p2.x) 
             + (p2.x * p2.x + p2.y * p2.y) * (p1.x - p3.x)
             + (p3.x * p3.x + p3.y * p3.y) * (p2.x - p1.x);
    y /= det;

    Circle c;
    Point p = {x, y};
    c.p = p;
    c.r = dist(p, p1);
    return c;
}

bool isThreePointsInLine(Point &p1, Point &p2, Point &p3) {
    // 삼각형 넓이 0이면 일직선 상에 있는 것 
    // 외적 이용하면 넓이 나옴 
    double x1 = p2.x - p1.x;
    double y1 = p2.y - p1.y;
    double x2 = p3.x - p1.x;
    double y2 = p3.y - p1.y;

    // 부동소수점 오차 정도는 허용 가정 
    double s = (x1 * y2 - x2 * y1) / 2;
    return fabs(s) < eps;
}

Circle circleFromPoints(vector<Point> &R) {
    Circle c;

    // base cases
    if(R.size() == 0) {
        c.p = {0, 0};
        c.r = 0;
    }
    else if(R.size() == 1) {
        c.p = R[0];
        c.r = 0;
    }
    else if(R.size() == 2) {
        // 같은 점인 경우 
        if(R[0].x == R[1].x && R[0].y == R[1].y) {
            c.p = R[0];
            c.r = 0;
        } else {
            // 두 점 중심
            c = circleFromTwoPoints(R[0], R[1]);
        }
    }
    else {
        // 점 3개로 원 만들기
        // 3개 점 일치 케이스 
        if(R[0].x == R[1].x && R[0].y == R[1].y && R[0].x == R[2].x && R[0].y == R[2].y) {
            c.p = R[0];
            c.r = 0;
        } 
        // 2개 점 일치 케이스 
        else if(R[0].x == R[1].x && R[0].y == R[1].y) {
            c = circleFromTwoPoints(R[0], R[2]);
        }
        else if(R[0].x == R[2].x && R[0].y == R[2].y) {
            c = circleFromTwoPoints(R[0], R[1]);
        }
        else if(R[1].x == R[2].x && R[1].y == R[2].y) {
            c = circleFromTwoPoints(R[0], R[1]);
        }
        // 일직선 상에 있는 경우 
        else if(isThreePointsInLine(R[0], R[1], R[2])) {
            // 거리 가장 먼 걸로 처리 
            Circle c1 = circleFromTwoPoints(R[0], R[1]);
            Circle c2 = circleFromTwoPoints(R[0], R[2]);
            Circle c3 = circleFromTwoPoints(R[1], R[2]);
            if(c1.r >= max(c2.r, c3.r)) c = c1;
            if(c2.r >= max(c1.r, c3.r)) c = c2;
            if(c3.r >= max(c1.r, c2.r)) c = c3;
        }
        // 3개로 원 만드는 경우 
        else {
            c = circleFromThreePoints(R[0], R[1], R[2]);
        }
    }

    return c;
}

bool isInside(Circle &c, Point &p) {
    // c 안에 p 들어가는지 체크 
    // 오차 범위 eps
    return dist(c.p, p) < c.r + eps;
}

Circle Welzl(vector<Point> &P, int idx, vector<Point> R) {
    // P : 전체 포인트 집합
    // idx : 제외할 포인트의 index
    // R : bound circle 계산할 포인트 집합 
    if(idx == 0 || R.size() == 3) {
        // idx == 0 : 더 이상 탐색할 거 없음 
        // R.size() == 3 : 3개 점으로 원 만들기 (2-dim)
        return circleFromPoints(R);
    }

    // idx - 1번째 제외
    Point p = P[idx - 1];
    Circle D = Welzl(P, idx - 1, R);
    // 제외되었던 것도 circle 안에 포함 
    if(isInside(D, p))
        return D;

    // 제외한 포인트 포함해서 다시 계산 
    R.push_back(p);
    return Welzl(P, idx - 1, R);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    init();
    vector<Point> R;
    Circle result = Welzl(points, points.size(), R);
    printf("%.2f", round(result.r * 2 * 100) / 100);
}
