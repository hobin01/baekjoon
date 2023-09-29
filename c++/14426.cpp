#include <iostream>

using namespace std;

int n, m;
string s;
int result;

struct Trie {
    Trie* ch[26]; // 소문자로 이루어짐 (ch 별로 트라이 포인터 부여)
    bool end; // 끝인지 확인용 

    // 트라이 생성자 
    Trie() {
        end = false;
        for (int i = 0; i < 26; i++) {
            ch[i] = NULL;
        }
    }

    // 트라이 소멸자
    ~Trie() {
        for (int i = 0; i < 26; i++) {
            if (ch[i] != NULL) {
                delete ch[i];
            }
        }
    }

    // 삽입
    // C 스타일 string 으로 처리 시 마지막에 null 이라 판단하기 쉬움
    void insert(const char* s) {
        // 끝에 도달
        if (*s == 0) {
            this->end = true;
            return;
        }

        // 현재 s가 가리키는 값
        int now = *s - 'a';

        // now에 해당하는 노드 없어서 새로 생성
        if (ch[now] == NULL)
            ch[now] = new Trie;

        // 이어서 탐색
        ch[now]->insert(s + 1);
    }

    // s가 trie에 있는 지 확인
    bool find(const char* s) {
        // s 끝까지 도달 
        if (*s == 0) {
            return true;
        }

        // 현재 s가 가리키는 값
        int now = *s - 'a';

        // now에 해당하는 값 없음
        if (ch[now] == NULL)
            return false;

        // 이어서 탐색
        return ch[now]->find(s + 1);
    }
};

void init(Trie* trie)
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> s;
        trie->insert(s.c_str());
    }
    result = 0;
}

void calc(Trie* trie)
{
    for (int i = 0; i < m; i++) {
        cin >> s;
        if (trie->find(s.c_str()))
            result++;
    }

    cout << result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Trie* root = new Trie;
    init(root);
    calc(root);
}