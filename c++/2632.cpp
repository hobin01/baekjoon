#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int pizza; // 구매하려는 피자 크기 
int m, n; // 조각 m, n개 

map<int,int> A; // 피자 A {크기 합:개수}
map<int,int> B; // 피자 B 

vector<int> vecA; // 피자 A 
vector<int> vecB; // 피자 B 

void init()
{
    cin >> pizza;
    cin >> m >> n;
    
    int num;
    vecA.resize(m);
    vecB.resize(n);
    
    int total = 0;
    for(int i = 0; i < m; i++) {
        cin >> num;
        vecA[i] = num;
        total += num;
    }
    A.insert({total, 1});
    
    total = 0;
    for(int i = 0; i < n; i++) {
        cin >> num;
        vecB[i] = num;
        total += num;
    }
    B.insert({total, 1});
}

void makeMap()
{
    // 모든 조각 합치는 건 처음에 포함 
    int sum, start, piece;
    for(start = 0; start < m; start++) {
        sum = 0;
        for(piece = 0; piece < (m - 1); piece++) {
            sum += vecA[(start + piece) % m];
            A[sum]++; // 키 없으면 A[sum] 초기값 (0) 들어가고 +1
        }
    }
    
    for(start = 0; start < n; start++) {
        sum = 0;
        for(piece = 0; piece < (n - 1); piece++) {
            sum += vecB[(start + piece) % n];
            B[sum]++;
        }
    }
}

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    init();
    makeMap();
    
    int result = 0;
   
    result += A[pizza];
    result += B[pizza];
    
    // 섞어 만드는 경우 
    auto iterA = A.begin();
    while(iterA != A.end()) {
        int pizzaA = iterA->first;
        int pizzaB = pizza - pizzaA;
        result += A[pizzaA] * B[pizzaB];
        iterA++;
    }
    
    cout << result;
}

