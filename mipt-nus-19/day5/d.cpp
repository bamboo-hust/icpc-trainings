#include <bits/stdc++.h>

using namespace std;

const int N = 102;
const int MOD = 998244353;

char s[N][N];
vector<int> a[N * N];

int com_id[N * N];
int num_com;
int n, m;

int id(int x, int y) {
    return (x - 1) * m + y;
}

int tin[N * N];
int timestamp;

void dfs(int u,  int &num_v, int &num_e, bool &self_loop) {
    tin[u] = ++timestamp;
    com_id[u] = num_com;
    num_v++;
    for (int v : a[u]) {
        if (!com_id[v]) {
            dfs(v, num_v, num_e, self_loop);
        }
        num_e += tin[v] >= tin[u];
        self_loop |= u == v;
    }
}

void add_edge(int u, int v) {
    a[v].push_back(u);
    if (u != v) a[u].push_back(v);
}

long long solve() {
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s[i][j] == '*') {
                bool up = i > 1 && s[i - 1][j] == '.';
                bool down = i < m && s[i + 1][j] == '.';
                bool left = j > 1 && s[i][j - 1] == '.';
                bool right = j < n && s[i][j + 1] == '.';
                if (up && down) {
                    add_edge(id(i - 1, j), id(i + 1, j));
                } else {
                    if (up) {
                        add_edge(id(i - 1, j), id(i - 1, j));
                    } else if (down) {
                        add_edge(id(i + 1, j), id(i + 1, j));
                    } else {
                        return 0;
                    }
                }
                if (left && right) {
                    add_edge(id(i, j - 1), id(i, j + 1));
                } else {
                    if (left) {
                        add_edge(id(i, j - 1), id(i, j - 1));
                    } else if (right) {
                        add_edge(id(i, j + 1), id(i, j + 1));
                    } else {
                        return 0;
                    }
                }
            }
        }
    }

    num_com = 0;
    for (int i = 1; i <= m * n; ++i) com_id[i] = 0;
    long long res = 1;
    timestamp = 0;
    for (int i = 1; i <= m * n; ++i) if (com_id[i] == 0) {
        int v = 0;
        int e = 0;
        bool self_loop = false;
        ++num_com;
        dfs(i, v, e, self_loop);
        //cerr << v << ' ' << e << endl;
        if (e > v) return 0;
        if (e == v) {
            if (!self_loop) {
                res = res * 2 % MOD;
            }
        } else {
            res = res * v % MOD;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        cin >> m >> n;
        for (int i = 1; i <= m; ++i) cin >> s[i] + 1;
        cout << solve() << '\n';
        for (int i = 1; i <= m * n; ++i) a[i].clear();
    }
}