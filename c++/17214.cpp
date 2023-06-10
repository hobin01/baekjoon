#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    cin >> s;
    
    // x^2, x 계수
    int a, b;
    
    // x위치 찾기
    int pos = s.find('x');
    
    // x있는 경우
    if(pos != -1) {
        // 상수항 있는 경우
        if(pos != s.size() - 1) {
            a = stoi(s.substr(0, pos)) / 2;
            b = stoi(s.substr(pos + 1, 10));
        }
        else {
            a = stoi(s.substr(0, pos)) / 2;
            b = 0;
        }
    }
    else {
        b = stoi(s);
        a = 0;
    }
    
    if(a == 0 && b == 0) {
        cout << "W";
        return 0;
    }
    
    if(a == 0) {
        if(b == 1) {
            cout << "x+W";
        }
        else if(b == -1) {
            cout << "-x+W";
        }
        else {
            cout << b << "x+W";
        }
        return 0;
    }
    
    else if(b == 0) {
        if(a == 1) {
            cout << "xx+W";
        }
        else if(a == -1) {
            cout << "-xx+W";
        }
        else {
            cout << a << "xx+W";
        }
        return 0;
    }
    
    else {
        if(a == 1 && b == 1) {
            cout << "xx+x+W";
        }
        else if(a == 1 && b == -1) {
            cout << "xx-x+W";
        }
        else if(a == -1 && b == 1) {
            cout << "-xx+x+W";
        }
        else if(a == -1 && b == -1) {
            cout << "-xx-x+W";
        }
        else if(a == 1 && b > 0) {
            cout << "xx+" << b << "x+W";
        }
        else if(a == 1 && b < 0) {
            cout << "xx" << b << "x+W";
        }
        else if(a == -1 && b > 0) {
            cout << "-xx+" << b << "x+W";
        }
        else if(a == -1 && b < 0) {
            cout << "-xx" << b << "x+W";
        }
        else if(b == 1) {
            cout << a << "xx+x+W";
        }
        else if(b == -1) {
            cout << a << "xx-x+W";
        }
        else if(b > 0) {
            cout << a << "xx+" << b << "x+W";
        }
        else if(b < 0) {
            cout << a << "xx" << b << "x+W";
        }
        
        return 0;
    }
}