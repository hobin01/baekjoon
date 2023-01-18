#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int T, N;
vector<ll> vec;
ll result;

void init()
{
    vec.clear();
    cin >> N;
    vec.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
    }

    result = 0;
}

void calc()
{
    ll tmp = 0; // 임시 최대값
    for (int i = N - 1; i >= 0; i--) {
        if (vec[i] < tmp)
            result += (tmp - vec[i]);
        else
            tmp = vec[i];
    }
}

int main()
{
    cin >> T;
    while (T--) {
        init();
        calc();
        cout << result << '\n';
    }
}