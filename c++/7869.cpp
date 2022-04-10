#include<iostream>
#include<cmath>
#include<algorithm>
#include<string>

using namespace std;

double pi = 3.14159265358979323846;
double X1, Y1, R1, X2, Y2, R2, result, dist;

// 원 중심 거리 구하기
double cal_dist()
{
	double X = (X2 - X1) * (X2 - X1);
	double Y = (Y2 - Y1) * (Y2 - Y1);
	return sqrt(X + Y);
}

void init()
{
	scanf_s("%lf %lf %lf %lf %lf %lf", &X1, &Y1, &R1, &X2, &Y2, &R2);
	dist = cal_dist();
}

// 안 겹침
double calc1()
{
	result = 0;
	return result;
}

// 한 원이 한 원 내부
double calc2()
{
	if (R1 < R2)
		return R1 * R1 * pi;
	else
		return R2 * R2 * pi;
}

// 두 원이 겹침
double calc3()
{
	double theta1 = acos((R1 * R1 + dist * dist - R2 * R2) / (2 * R1 * dist));
	double theta2 = acos((R2 * R2 + dist * dist - R1 * R1) / (2 * R2 * dist));
	
	theta1 = theta1 * 2;
	theta2 = theta2 * 2;

	double S1 = (R1 * R1 * theta1 * 0.5) - (R1 * R1 * sin(theta1) * 0.5);
	double S2 = (R2 * R2 * theta2 * 0.5) - (R2 * R2 * sin(theta2) * 0.5);

	return S1 + S2;
}

// n번째 자리에서 반올림
double round(double num, int n)
{
	double t = pow(10, n - 1);
	return round(num * t) / t;
}

int main()
{
	init();
	if ((R1 + R2) < dist)
		printf("%.03f", result);
	else if (abs(R2 - R1) >= dist) {
		result = calc2();
		result = round(result, 4);
		printf("%.03f", result);
	}
	else {
		result = calc3();
		result = round(result, 4);
		printf("%.03f", result);
	}
}