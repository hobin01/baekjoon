#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int n, m;

const int treeStartIdx = 131072; // 최대 입력 10만개 
const int treeSize = 262144;
const int maxInputSize = 100000;
const int inf = INT_MAX;

int nums[maxInputSize]; // 입력값 
int maxIndexTree[treeSize];
int minIndexTree[treeSize];

void updateTree(int idx)
{
    int num = nums[idx];
    int treeIdx = idx + treeStartIdx;
    
    while(treeIdx > 0) {
        // maxIndexTree 업데이트 
        maxIndexTree[treeIdx] = max(maxIndexTree[treeIdx], num);
        // minIndexTree 업데이트 
        minIndexTree[treeIdx] = min(minIndexTree[treeIdx], num);
        treeIdx >>= 1;
    }
}

void init()
{
    cin >> n >> m;
    fill(nums, nums + maxInputSize, 0);
    fill(maxIndexTree, maxIndexTree + treeSize, 0);
    fill(minIndexTree, minIndexTree + treeSize, inf);
    
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
        updateTree(i);
    }
}

int getMaxNum(int idx1, int idx2)
{
    int res = 0;
    int treeIdx1 = idx1 + treeStartIdx;
    int treeIdx2 = idx2 + treeStartIdx;
    
    while(treeIdx1 <= treeIdx2) {
        if(!(treeIdx1 & 1)) {
            treeIdx1 >>= 1;
        }
        else {
            res = max(res, maxIndexTree[treeIdx1]);
            treeIdx1 = (treeIdx1 + 1) >> 1;
        }
        
        if(!(treeIdx2 & 1)) {
            res = max(res, maxIndexTree[treeIdx2]);
            treeIdx2 = (treeIdx2 - 1) >> 1;
        }
        else {
            treeIdx2 >>= 1;   
        }
    }
    
    return res;
}

int getMinNum(int idx1, int idx2)
{
    int res = inf;
    int treeIdx1 = idx1 + treeStartIdx;
    int treeIdx2 = idx2 + treeStartIdx;
    
    while(treeIdx1 <= treeIdx2) {
        if(!(treeIdx1 & 1)) {
            treeIdx1 >>= 1;
        }
        else {
            res = min(res, minIndexTree[treeIdx1]);
            treeIdx1 = (treeIdx1 + 1) >> 1;
        }
        
        if(!(treeIdx2 & 1)) {
            res = min(res, minIndexTree[treeIdx2]);
            treeIdx2 = (treeIdx2 - 1) >> 1;
        }
        else {
            treeIdx2 >>= 1;   
        }
    }
    
    return res;
}

pair<int, int> query(int idx1, int idx2)
{
    pair<int, int> res = {-1, -1};
    
    res.first = getMinNum(idx1, idx2);
    res.second = getMaxNum(idx1, idx2);
    
    return res;
}

void game()
{
    int idx1, idx2;
    pair<int, int> res;
    for(int i = 0; i < m; i++) {
        cin >> idx1 >> idx2;
        res = query(idx1 - 1, idx2 - 1);
        cout << res.first << ' ' << res.second << '\n';
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    game();
}