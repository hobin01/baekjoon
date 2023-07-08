#include <iostream>
using namespace std;
int main()
{
    double r1, r2, r3;
    cin >> r1 >> r2 >> r3;
    printf("%.6f", 1/(1/r1 + 1/r2 + 1/r3));
}