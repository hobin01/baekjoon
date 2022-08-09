#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // 오름차순 우선순위 큐
    priority_queue<int, vector<int>, greater<int> >pq;
    int n;
    int num;
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> num;    
            pq.push(num);
        }
        // push 하면 작은 애는 날라감
        while(pq.size() > n)
            pq.pop();
    }

    // 남은 애의 top = n번째 큰 수    
    cout << pq.top();
}