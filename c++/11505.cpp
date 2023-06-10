#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;
int n, m ,k;
int a, b;
ll c;
ll mod = 1000000007;
int height;

vector<ll> nums;
vector<ll> tree;

ll init(int start, int last, int node)
{
    // start, last : 원래 배열 인덱스
    // node : 세그먼트 트리 인덱스
    // 세그먼트 트리 구성 시 좌우 구분에 *2로 할려고 1부터 시작
    if(start == last) {
        tree[node] = nums[start];
        return tree[node];
    }
    int mid = (start + last) / 2;
    ll left_tree = init(start, mid, node * 2) % mod;
    ll right_tree = init(mid + 1, last, node * 2 + 1) % mod;
    tree[node] = (left_tree * right_tree) % mod;
    return tree[node];
}

ll mul(int start, int last, int node, int left, int right)
{
    // left, right : 구간 인덱스
    
    // 범위 밖
    if(left > last || right < start)
        return 1;
    // 범위 안
    if(left <= start && last <= right)
        return tree[node];
    // 나머지 경우
    int mid = (start + last) / 2;
    ll left_mul = mul(start, mid, node * 2, left, right) % mod;
    ll right_mul = mul(mid + 1, last, node * 2 + 1, left, right) % mod;
    return (left_mul * right_mul) % mod;
}

ll update(int start, int last, int node, int idx, ll val)
{
    // idx : 수정할 인덱스
    
    // 범위 밖
    if(idx < start || idx > last)
        return tree[node];
    // 해당 인덱스
    if(start == last) {
        tree[node] = val;
        return tree[node];
    }
    int mid = (start + last) / 2;
    ll left_tree = update(start, mid, node * 2, idx, val) % mod;
    ll right_tree = update(mid + 1, last, node * 2 + 1, idx, val) % mod;
    tree[node] = (left_tree * right_tree) % mod;
    return tree[node];
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m >> k;
    nums.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    height = (int)ceil(log2(n));
    tree.resize(1 << (height + 1));
    
    int calc_count = m + k;
    n--;
    
    init(0, n, 1);
    
    while(calc_count--) {
        cin >> a >> b >> c;
        if(a == 1) {
            b--;
            
            // 업데이트
            update(0, n, 1, b, c);
        }
        else {
            int c2 = (int)c;
            if(b > c2) {
                swap(b, c2);
            }
            b--;
            c2--;
            
            // 곱 구하기
            cout << mul(0, n, 1, b, c2) << '\n';
        }
    }
}