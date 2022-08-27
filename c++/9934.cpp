#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

int k;
vector<int> nums;
vector<int> tree[10];
bool check[1025];
int total;

void init()
{
    cin >> k;
    int num;
    
    total = (int)pow(2, k) - 1;
    for(int i = 0; i < total; i++) {
        cin >> num;
        nums.push_back(num);
    }
    memset(check, false, sizeof(check));
}

void travel(int depth, int start, int last)
{
    
    // 중위 순회 되도록 만들기 (왼 부모 오 순 되도록 만듬)
    int mid = (start + last) / 2;
    int num = nums[mid];
    if(check[num])
        return;
    
    tree[depth].push_back(num);
    check[num] = true;
    
    travel(depth + 1, start, mid);
    travel(depth + 1, mid + 1, last);
}


int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    
    travel(0, 0, total);
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < tree[i].size(); j++) {
            cout << tree[i][j] << ' ';
        }
        cout << '\n';
    }
}