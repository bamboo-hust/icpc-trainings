#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

string s, t;
int nxt[N][26][2];
int f[2];

bool contains(string s, string t) {
    for (int j = 0; j < 26; ++j) {
        for (int k = 0; k <= 1; ++k) {
            nxt[t.size()][j][k] = t.size() + 1;
        }
    }
    for (int i = t.size() - 1; i >= 0; --i) {
        for (int j = 0; j < 26; ++j) {
            for (int k = 0; k <= 1; ++k) {
                if ((k == i % 2) && t[i] - 'a' == j) {
                    nxt[i][j][k] = i;
                } else {
                    nxt[i][j][k] = nxt[i + 1][j][k];
                }
            }
        }
    }
    f[0] = t.size();
    f[1] = 0;
    for (int i = 0; i < s.size(); ++i) {
        int g[2] = {(int)t.size(), (int)t.size()};
        for (int k = 0; k <= 1; ++k) if (f[!k] < t.size()) {
            if (nxt[f[!k]][s[i] - 'a'][k] < t.size()) {
                g[k] = nxt[f[!k]][s[i] - 'a'][k];
            }
        }
        f[0] = g[0] + 1;
        f[1] = g[1] + 1;
        //cerr << i << ' ' << f[0] << ' ' << f[1] << endl;
    }
    return f[!(t.size() % 2)] <= t.size();
}

int main() {
    cin >> s >> t;
    cout << (contains(s, t) ? "YES" : "NO") << endl;
}