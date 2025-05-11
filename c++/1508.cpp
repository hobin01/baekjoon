#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int n, m, k;
vector<int> referee;

void init() {
    cin >> n >> m >> k;
    referee.resize(n);
    for(int i = 0; i < k; i++) {
        cin >> referee[i];
    }
}

bool possible(int d) {
    // d 간격으로 m 명 고를 수 있는 지 체크 

    // 첫 사람은 무조건 
    // 첫 사람 포함된 간격이 정답이라면 사전순에서는 첫 사람 무조건 포함 
    // 아니더라도 뒤에서 결정되면 앞에는 상관없으니 사전순에서는 첫 사람 무조건 포함 
    int cnt = 1; 
    int last = referee[0];
    for(int i = 1; i < k; i++) {
        if((referee[i] - last) >= d) {
            last = referee[i];
            cnt++;
            if(cnt == m) return true;
        }
    }
    return false;
}

int biggest_nearest() {
    int low = 0;
    int high = n;
    int mid;

    while(low < high) {
        mid = (low + high + 1) / 2;
        if(possible(mid)) low = mid;
        else high = mid - 1;
    }

    return low;
}

string calc() {
    int d = biggest_nearest();

    vector<int> vec(k, 0);
    vec[0] = 1;
    int last = referee[0];
    int cnt = 1;

    // 사전 순으로 제일 빠르도록 d 조건 만족하는 거 계산
    // 0번째 무조건 포함 
    // 0번째 포함된 게 가장 가까운 거라면 포함해야 정답
    // 아닌 경우라도, 0번 째 뒤에서 가장 가까운 무엇인가 골라진건데
    // 그 상황에서도 사전 순이라면 0번째는 무조건 포함 

    for(int i = 1; i < k; i++) {
        if(referee[i] - last >= d) {
            last = referee[i];
            vec[i] = 1;
            cnt++;

            if(cnt == m) break;
        }
    }

    // 결과 계산 
    string res(k, '0');
    for(int i = 0; i < k; i++) {
        res[i] = '0' + vec[i];
    }

    return res;
}

int main() {
    init();
    cout << calc();
}
