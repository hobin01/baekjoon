#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double a, b, c;
    double S, R, r, d, k;
    cin >> a >> b >> c;
    
    double s = (a + b + c) / 2;
    S = sqrt(s*(s-a)*(s-b)*(s-c));
    R = (a*b*c)/(4*S);
    r = (2*S)/(a+b+c);
    if(a==b && b==c)
        d = 0;
    else if(R*(R-2*r) <= 0)
        d = 0;
    else 
        d = sqrt(R*(R-2*r));
    k = sqrt(R*R-(a/2)*(a/2))+sqrt(R*R-(b/2)*(b/2))+sqrt(R*R-(c/2)*(c/2));
    
    printf("%.9f\n%.9f\n%.9f\n%.9f\n%.9f", S, R, r, d, k);
}