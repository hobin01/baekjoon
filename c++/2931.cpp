#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

int r, c;
int board[26][26];
map<char, int> m;
pair<int, int> result;
char pipe;

// | : 5, - : 6, + : 7
// . : 0, M, Z : -1

// 나와도 되는 부분들 (-1은 항상 가능)

// | : 위 : |, +, 1, 4 아래 : |, +, 2, 3  // 왼 : ., |, 3, 4 오른 : ., |, 1, 2
// - : 왼 : -, +, 1, 2 오른 : -, +, 3, 4 // 위 : ., -, 2, 3 아래 : ., -, 1, 4

// + : 위 : +, |, 1, 4 아래 : +, |, 2, 3 
// 왼 : +, -, 1, 2 오른 : +, -, 3, 4 

// 1 : 오른 : -, +, 3, 4 아래 : |, +, 2, 3 // 왼 : ., |, 3, 4 위 : ., -, 2, 3
// 2 : 오른 : -, +, 3, 4 위 : |, +, 1, 4 // 왼 : ., |, 3, 4 아래 : ., -, 1, 4
// 3 : 왼 : -, +, 1, 2 위 : |, +, 1, 4  // 오른 : ., |, 1, 2 아래 : ., -, 1, 4
// 4 : 왼 : -, +, 1, 2 아래 : |, +, 2, 3 // 오른 : ., |, 1, 2 위 : ., -, 2, 3

void init()
{
    m.insert({'.', 0});
    m.insert({'M', -1});
    m.insert({'Z', -1});
    m.insert({'1', 1});
    m.insert({'2', 2});
    m.insert({'3', 3});
    m.insert({'4', 4});
    m.insert({'|', 5});
    m.insert({'-', 6});
    m.insert({'+', 7});
    
    cin >> r >> c;
    for(int i = 1; i <= r; i++) {
        for(int j = 1; j <= c; j++) {
            char c;
            cin >> c;
            board[i][j] = m[c];
        }
    }
    
    result = {-1, -1};
}

pair<int,int> pos_calc(int y, int x)
{
    if(board[y][x] == 0 || board[y][x] == -1)
        return {-1, -1};
    
    if(board[y][x] == 1) {
        if(board[y][x+1] == 0) {
            return {y, x+1};
        }
        else if(board[y+1][x] == 0) {
            return {y+1, x};
        }
    }
    
    else if(board[y][x] == 2) {
        if(board[y][x+1] == 0) {
            return {y, x+1};
        }
        else if(board[y-1][x] == 0) {
            return {y-1, x};
        }
    }
    
    else if(board[y][x] == 3) {
        if(board[y][x-1] == 0) {
            return {y, x-1};
        }
        else if(board[y-1][x] == 0) {
            return {y-1, x};
        }
    }
    
    else if(board[y][x] == 4) {
        if(board[y][x+1] == 0) {
            return {y, x+1};
        }
        else if(board[y+1][x] == 0) {
            return {y+1, x};
        }
    }
    
    else if(board[y][x] == 5) {
        if(board[y-1][x] == 0) {
            return {y-1, x};
        }
        else if(board[y+1][x] == 0) {
            return {y+1, x};
        }
    }
    
    else if(board[y][x] == 6) {
        if(board[y][x-1] == 0) {
            return {y, x-1};
        }
        else if(board[y][x+1] == 0) {
            return {y, x+1};
        }
    }
    
    else if(board[y][x] == 7) {
        if(board[y-1][x] == 0) {
            return {y-1, x};
        }
        else if(board[y+1][x] == 0) {
            return {y+1, x};
        }
        else if(board[y][x-1] == 0) {
            return {y, x-1};
        }
        else if(board[y][x+1] == 0) {
            return {y, x+1};
        }
    }
    
    return {-1, -1};
}

bool check(int p)
{
    // 제대로 찾았는 지 확인 
    // int p = m[pipe];
    int y = result.first;
    int x = result.second;
    
    bool chk = true;
    if(p == 1) {
        chk &= (x+1 <= c);
        if(chk == false)
            return chk;
            
        chk &= (board[y][x+1] == 6 || board[y][x+1] == 7 || board[y][x+1] == 3 || board[y][x+1] == 4 || board[y][x+1] == -1);
            
        chk &= (y+1 <= r);
        if(chk == false)
            return chk;
        
        chk &= (board[y+1][x] == 5 || board[y+1][x] == 7 || board[y+1][x] == 2 || board[y+1][x] == 3 || board[y+1][x] == -1);
        
        if(x-1 >= 1) {
            chk &= (board[y][x-1] == 0 || board[y][x-1] == 5 || board[y][x-1] == 3 || board[y][x-1] == 4 || board[y][x-1] == -1);
        }
        if(y-1 >= 1) {
            chk &= (board[y-1][x] == 0 || board[y-1][x] == 6 || board[y-1][x] == 2 || board[y-1][x] == 3 || board[y-1][x] == -1);
        }
    }
    
    else if(p == 2) {
        chk &= (x+1 <= c);
        if(chk == false)
            return chk;
        
        chk &= (board[y][x+1] == 6 || board[y][x+1] == 7 || board[y][x+1] == 3 || board[y][x+1] == 4 || board[y][x+1] == -1);
            
        chk &= (y-1 >= 1);
        if(chk == false)
            return chk;
        
        chk &= (board[y-1][x] == 5 || board[y-1][x] == 7 || board[y-1][x] == 1 || board[y-1][x] == 4 || board[y-1][x] == -1);
        
        if(x-1 >= 1) {
            chk &= (board[y][x-1] == 0 || board[y][x-1] == 5 || board[y][x-1] == 3 || board[y][x-1] == 4 || board[y][x-1] == -1);
        }
        
        if(y+1 <= r) {
            chk &= (board[y+1][x] == 0 || board[y+1][x] == 6 || board[y+1][x] == 1 || board[y+1][x] == 4 || board[y+1][x] == -1);
        }
    }
    
    else if(p == 3) {
        chk &= (x-1 >= 1);
        if(chk == false)
            return chk;
        
        chk &= (board[y][x-1] == 6 || board[y][x-1] == 7 || board[y][x-1] == 1 || board[y][x-1] == 2 || board[y][x-1] == -1);
            
        chk &= (y-1 >= 1);
        if(chk == false)
            return chk;
            
        chk &= (board[y-1][x] == 5 || board[y-1][x] == 7 || board[y-1][x] == 1 || board[y-1][x] == 4 || board[y-1][x] == -1);
        
        if(x+1 <= c) {
            chk &= (board[y][x+1] == 0 || board[y][x+1] == 5 || board[y][x+1] == 1 || board[y][x+1] == 2 || board[y][x+1] == -1);
        }
        
        if(y+1 <= r) {
            chk &= (board[y+1][x] == 0 || board[y+1][x] == 6 || board[y+1][x] == 1 || board[y+1][x] == 4 || board[y+1][x] == -1);
        }
    }
    
    else if(p == 4) {
        chk &= (x-1 >= 1);
        if(chk == false)
            return chk;
        
        chk &= (board[y][x-1] == 6 || board[y][x-1] == 7 || board[y][x-1] == 1 || board[y][x-1] == 2 || board[y][x-1] == -1);
        
        chk &= (y+1 <= r);
        if(chk == false)
            return chk;
            
        chk &= (board[y+1][x] == 5 || board[y+1][x] == 7 || board[y+1][x] == 2 || board[y+1][x] == 3 || board[y+1][x] == -1);
        
        if(x+1 <= c) {
            chk &= (board[y][x+1] == 0 || board[y][x+1] == 5 || board[y][x+1] == 1 || board[y][x+1] == 2 || board[y][x+1] == -1);
        }
        
        if(y-1 >= 1) {
            chk &= (board[y-1][x] == 0 || board[y-1][x] == 6 || board[y-1][x] == 2 || board[y-1][x] == 3 || board[y-1][x] == -1);
        }
    }
    
    else if(p == 5) {
        chk &= (y-1 >= 1);
        if(chk == false)
            return chk;
            
        chk &= (board[y-1][x] == 5 || board[y-1][x] == 7 || board[y-1][x] == 1 || board[y-1][x] == 4 || board[y-1][x] == -1);
        
        chk &= (y+1 <= r);
        if(chk == false)
            return chk;
            
        chk &= (board[y+1][x] == 5 || board[y+1][x] == 7 || board[y+1][x] == 2 || board[y+1][x] == 3 || board[y+1][x] == -1);
        
        if(x-1 >= 1) {
            chk &= (board[y][x-1] == 0 || board[y][x-1] == 5 || board[y][x-1] == 3 || board[y][x-1] == 4 || board[y][x-1] == -1);
        }
        
        if(x+1 <= c) {
            chk &= (board[y][x+1] == 0 || board[y][x+1] == 5 || board[y][x+1] == 1 || board[y][x+1] == 2 || board[y][x+1] == -1);
        }
    }
    
    else if(p == 6) {
        chk &= (x-1 >= 1);
        if(chk == false)
            return chk;
            
        chk &= (board[y][x-1] == 6 || board[y][x-1] == 7 || board[y][x-1] == 1 || board[y][x-1] == 2 || board[y][x-1] == -1);
        
        chk &= (x+1 <= c);
        if(chk == false)
            return chk;
            
        chk &= (board[y][x+1] == 6 || board[y][x+1] == 7 || board[y][x+1] == 3 || board[y][x+1] == 4 || board[y][x+1] == -1);
        
        if(y-1 >= 1) {
            chk &= (board[y-1][x] == 0 || board[y-1][x] == 6 || board[y-1][x] == 2 || board[y-1][x] == 3 || board[y-1][x] == -1);
        }
        
        if(y+1 <= r) {
            chk &= (board[y+1][x] == 0 || board[y+1][x] == 6 || board[y+1][x] == 1 || board[y+1][x] == 4 || board[y+1][x] == -1);
        }
    }
    
    else if(p == 7) {
        chk &= (y-1 >= 1);
        if(chk == false)
            return chk;
            
        chk &= (board[y-1][x] == 7 || board[y-1][x] == 5 || board[y-1][x] == 1 || board[y-1][x] == 4 || board[y-1][x] == -1);
        
        chk &= (y+1 <= r);
        if(chk == false)
            return chk;
            
        chk &= (board[y+1][x] == 7 || board[y+1][x] == 5 || board[y+1][x] == 2 || board[y+1][x] == 3 || board[y+1][x] == -1);
        
        chk &= (x-1 >= 1);
        if(chk == false)
            return chk;
            
        chk &= (board[y][x-1] == 7 || board[y][x-1] == 6 || board[y][x-1] == 1 || board[y][x-1] == 2 || board[y][x-1] == -1);
        
        chk &= (x+1 <= c);
        if(chk == false)
            return chk;
            
        chk &= (board[y][x+1] == 7 || board[y][x+1] == 6 || board[y][x+1] == 3 || board[y][x+1] == 4 || board[y][x+1] == -1);
    }
    
    return chk;
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    for(int y = 1; y <= r; y++) {
        for(int x = 1; x <= c; x++) {
            result = pos_calc(y, x);
            if(result.first != -1) {
                
                for(int p = 1; p <= 7; p++) {
                    bool chk = check(p);
                    
                    if(chk) {
                        for(auto iter = m.begin(); iter != m.end(); iter++) {
                            if(iter->second == p) {
                                pipe = iter->first;
                                break;
                            }
                        }
                        cout << result.first << ' ' << result.second << ' ' << pipe;
                        return 0;
                    }
                }    
            }
        }
        
    }
}