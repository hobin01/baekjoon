#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// 입력으로 주어지는 곳 y,x 찾고
// 이동 후 위치는 반으로 나눴을 때
// y 축 기준
// 작은 범위 1,2 / 큰 범위 3,4
// x 축 기준
// 작은 범위 2,3 / 큰 범위 1,4
// 공통으로 나오는 거가 정답

int d;
long long x, y;
string start;
string result;
long long pow2;

void init()
{
    cin >> d >> start;
    cin >> x >> y;
    result.resize(d);
    pow2 = 1LL << d;
}

pair<long long, long long> calcYX(string s)
{
    pair<long long, long long> point = { 0, 0 };

    // y, x 좌표 구하기
    long long startY = 1LL;
    long long startX = 1LL;
    long long lastY = pow2;
    long long lastX = pow2;

    for (int i = 0; i < d - 1; i++) {
        int num = start[i] - '0';
        long long halfY = (lastY - startY + 1) / 2;
        long long halfX = (lastX - startX + 1) / 2;
        if (num == 1 || num == 2) {
            lastY = startY + halfY - 1;
        }
        else {
            startY = startY + halfY;
        }

        if (num == 2 || num == 3) {
            lastX = startX + halfX - 1;
        }
        else {
            startX = startX + halfX;
        }
    }

    if (start[d - 1] == '1' || start[d - 1] == '2') {
        point.first = startY;
    }
    else {
        point.first = lastY;
    }

    if (start[d - 1] == '2' || start[d - 1] == '3') {
        point.second = startX;
    }
    else {
        point.second = lastX;
    }

    return point;
}

// 공통값 계산용
int commonNum(int y1, int y2, int x1, int x2) {
    if (y1 == x1)
        return y1;
    if (y1 == x2)
        return y1;
    if (y2 == x1)
        return y2;
    if (y2 == x2)
        return y2;

    return 0;
}

void calc()
{
    pair<long long, long long> startPoint = calcYX(start);

    // 위쪽이 양수 입력
    long long dstY = startPoint.first - y;
    long long dstX = startPoint.second + x;

    // 범위 벗어나는 경우
    if (dstY <= 0 || dstY > pow2 || dstX <= 0 || dstX > pow2) {
        cout << -1;
        return;
    }

    vector<int> vecY[2]; // y 좌표보고 추정한 값
    vector<int> vecX[2]; // x 좌표보고 추정한 값

    long long startY = 1LL;
    long long startX = 1LL;
    long long lastY = pow2;
    long long lastX = pow2;

    // dst y,x 추정하기
    for (int i = 0; i < d; i++) {
        long long halfY = (lastY - startY + 1) / 2;
        long long halfX = (lastX - startX + 1) / 2;

        if (startY <= dstY && dstY < startY + halfY) {
            vecY[0].push_back(1);
            vecY[1].push_back(2);
            lastY = startY + halfY - 1;
        }
        else {
            vecY[0].push_back(3);
            vecY[1].push_back(4);
            startY = startY + halfY;
        }

        if (startX <= dstX && dstX < startX + halfX) {
            vecX[0].push_back(2);
            vecX[1].push_back(3);
            lastX = startX + halfX - 1;
        }
        else {
            vecX[0].push_back(1);
            vecX[1].push_back(4);
            startX = startX + halfX;
        }
    }

    // 공통 값 계산
    for (int i = 0; i < d; i++) {
        int y1 = vecY[0][i];
        int y2 = vecY[1][i];
        int x1 = vecX[0][i];
        int x2 = vecX[1][i];

        int num = commonNum(y1, y2, x1, x2);
        result[i] = '0' + num;
    }

    cout << result;

    return;
}

int main()
{
    init();
    calc();
}