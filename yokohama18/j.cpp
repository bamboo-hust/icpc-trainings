#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int LOG = 20;

int n;
int par[LOG][N], lv[N], c[N];
int in[N], out[N], cntEuler;
vector<int> adj[N];

void dfsInit(int u, int p) {
    in[u] = ++cntEuler;
    lv[u] = lv[p] + 1;
    par[0][u] = p;
    for (int i = 1; i < LOG; i++) par[i][u] = par[i - 1][par[i - 1][u]];
    for (int v : adj[u]) {
        if (v == p) continue;
        dfsInit(v, u);
    }
    out[u] = cntEuler;
}

int getPar(int u, int k) {
    for (int i = 0; i < LOG; i++) {
        if (k >> i & 1) u = par[i][u];
    }
    return u;
}

int lca(int u, int v) {
    if (lv[u] < lv[v]) swap(u, v);
    int k = lv[u] - lv[v];
    u = getPar(u, k);
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
        if (par[i][u] != par[i][v]) {
            u = par[i][u];
            v = par[i][v];
        }
    }
    return par[0][u];
}


struct Color {
    set<pair<int, int>> ls;
    int res = 0, root = 0;

    void add(int u) {
        if (ls.empty()) {
            root = u;
            ls.insert({in[u], u});
            return;
        }
        int v = 0;
        auto it = ls.lower_bound({in[u], u});
        if (it != ls.end()) {
            int w = lca(u, it->second);
            if (lv[w] > lv[v]) v = w;
        }
        if (it != ls.begin()) {
            it--;
            int w = lca(u, it->second);
            if (lv[w] > lv[v]) v = w;
        }
        res += lv[u] - lv[v];
        if (lv[v] < lv[root]) {
            res += lv[root] - lv[v];
            root = v;
        }
        ls.insert({in[u], u});
    }

    void remove(int u) {
        ls.erase({in[u], u});
        if (ls.empty()) {
            res = root = 0;
            return;
        }
        int v = 0;
        auto it = ls.lower_bound({in[u], u});
        if (it != ls.end()) {
            int w = lca(u, it->second);
            if (lv[w] > lv[v]) v = w;
        }
        if (it != ls.begin()) {
            it--;
            int w = lca(u, it->second);
            if (lv[w] > lv[v]) v = w;
        }
        res -= lv[u] - lv[v];
        int newRoot = lca(ls.begin()->second, ls.rbegin()->second);
        if (lv[newRoot] > lv[v]) {
            res -= lv[newRoot] - lv[v];
            root = newRoot;
        }
    }

    int getRes() {
        return root ? res : -1;
    }

//    void debug() {
//        cout << res << ' ' << root << endl;
//    }
} color[N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v); adj[v].push_back(u);
    }
    dfsInit(1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        color[c[i]].add(i);
    }
//    for (int i = 1; i <= n; i++) {
//        color[i].debug();
//    }
    int m; cin >> m;
    while (m--) {
        char op; cin >> op;
        if (op == 'U') {
            int x, y; cin >> x >> y;
//            cout << "update " << x << ' ' << y << endl;
            color[c[x]].remove(x);
//            color[c[x]].debug();
            c[x] = y;
            color[c[x]].add(x);
//            color[c[x]].debug();
        } else {
            int x; cin >> x;
            cout << color[x].getRes() << '\n';
        }
    }
    return 0;
}