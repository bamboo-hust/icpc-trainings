#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

map<string, int> id;
int par[N];
int n, m, q;
int num[N];
set<int> has[N];

int getPar(int u) {
    if (par[u] == 0) {
        return u;
    }
    return par[u] = getPar(par[u]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        id[s] = i;
        has[i].insert(i);
        num[i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        int r;
        string x, y;
        cin >> r >> x >> y;
        int u = id[x];
        int v = id[y];
        int change = num[u] ^ num[v] ^ r;
        u = getPar(u);
        v = getPar(v);
        if (u == v) {
            continue;
        }
        if (has[u].size() > has[v].size()) {
            swap(u, v);
        }
        for (set<int>::iterator it = has[u].begin(); it != has[u].end(); it++) {
            int foo = *it;
            num[foo] ^= change;
            has[v].insert(foo);
        }
        par[u] = v;
    }   
    while (q--) {
        string x, y;
        cin >> x >> y;
        int u = id[x];
        int v = id[y];
        int uu = u;
        int vv = v;
        u = getPar(u);
        v = getPar(v);
        if (u != v) {
            cout << "2\n";
        } else if (num[uu] == num[vv]) {
            cout << "0\n";
        } else {
            cout << "1\n";
        }
    }
    return 0;
}