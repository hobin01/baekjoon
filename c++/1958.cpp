#include <iostream>
#include <string>
#include <cstring>
using namespace std;

string s1, s2, s3;
int lcs[101][101][101];

void init()
{
    cin >> s1 >> s2 >> s3;
    string s = "0";
    s1 = s + s1;
    s2 = s + s2;
    s3 = s + s3;
    memset(lcs, 0, sizeof(lcs));
}

void calc()
{
    for(int i = 0; i < s1.size(); i++) {
        for(int j = 0; j < s2.size(); j++) {
            for(int k = 0; k < s3.size(); k++) {
                if(i == 0 || j == 0 || k == 0) {
                    lcs[i][j][k] = 0;
                    continue;
                }
                
                if(s1[i] == s2[j] && s2[j] == s3[k]) {
                    lcs[i][j][k] = lcs[i-1][j-1][k-1] + 1;
                }
                else {
                    lcs[i][j][k] = max(max(lcs[i-1][j][k], lcs[i][j-1][k]), lcs[i][j][k-1]);
                }
            }
        }
    }
    
    cout << lcs[s1.size() - 1][s2.size() - 1][s3.size() - 1];
}

int main()
{
    init();
    calc();
}