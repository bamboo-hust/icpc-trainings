#include <bits/stdc++.h>

using namespace std;

const int N = 50010;
const int CHR = 26;
const int M = 44;

int n;

struct Trie {
    int nxt[CHR][2 * N * M];
    int g[2 * N * M];
    int cnt;

    Trie() {
        memset(nxt, -1, sizeof nxt);
        cnt = 0;
    }

    void init() {
        for (int i = 0; i <= cnt; i++) {
            g[i] = 0;
            for (int j = 0; j < CHR; j++) {
                nxt[j][i] = -1;
            }
        }
        cnt = 0;
    }

    void add(const string &u) {
        int cur = 0;
        vector<int> ls = {0};
        for (char v : u) {
            int id = v - 'a';
            if (nxt[id][cur] == -1) {
                nxt[id][cur] = ++cnt;
            }
            cur = nxt[id][cur];
            ls.push_back(cur);
        }
        for (int i = ls.size() - 1; i >= 0; i--) {
            int id = ls[i];
            g[id] = 0;
            for (int j = 0; j < CHR; j++) {
                int v = nxt[j][id];
                if (v != -1) {
                    g[id] ^= (g[v] + 1);
                }
            }
        }
    }

    int getRes() {
        if (g[0] == 0) return 2;
        return 1;
    }
} t;

void init() {
    t.init();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        cout << "Case " << test << ":\n";
        cin >> n;

        init();
        for (int i = 1; i <= n; i++) {
            string u;
            cin >> u;
            t.add(u);
        }   
        int q;
        cin >> q;
        while (q--) {
            string u;
            cin >> u;
            t.add(u);
            cout << t.getRes() << '\n';
        }
    }   
    return 0;
}