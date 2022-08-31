#include <iostream>
#include <cstring>

using namespace std;

int n, k, s;

bool graph[401][401]; // [i][j] : i -> j 존재하면 true (j가 먼저 일어난 사건)

void init()
{
    cin >> n >> k;
    memset(graph, sizeof(graph), false);

    int before, after;    
    for(int i = 0; i < k; i++) {
        cin >> before >> after;
        graph[after][before] = true;
    }
    
    for(int i = 1; i <= n; i++){
        graph[i][i] = true;
    }
}

void calc()
{
    // 플로이드 와샬 응용
    // 경로 유무만 파악하면 되므로 and로 계산
    // i -> k true and k -> j true => i -> j true
    // n <= 400 이므로 n^3 가능 
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(graph[i][j] == true)
                    continue;
                graph[i][j] = graph[i][k] & graph[k][j];
            }
        }
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    calc();
    
    cin >> s;
    int a, b;
    for(int i = 0; i < s; i++) {
        cin >> a >> b;
        if(graph[a][b] == false && graph[b][a] == false) {
            // 경로 없는 경우
            cout << 0 << '\n';
        }
        else if(graph[a][b] == false && graph[b][a] == true) {
            // a가 먼저 일어난 사건인 경우
            cout << -1 << '\n';
        }
        else if(graph[a][b] == true && graph[b][a] == false) {
            // b가 먼저 일어난 사건인 경우
            cout << 1 << '\n';
        }
        else {
            // 모순 없음
            continue;
        }
    }
}

