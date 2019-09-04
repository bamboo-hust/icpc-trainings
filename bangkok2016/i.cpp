#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int Q =  50010;
const int LOG = 20;

int n, q, r;
int lv[N];
int numChild[N];
int par[LOG][N];
vector<int> adj[N];

void dfs(int u, int p) {
    lv[u] = lv[p] + 1;
    numChild[u] = 1;
    par[0][u] = p;
    for (int i = 1; i < LOG; i++) {
        par[i][u] = par[i - 1][par[i - 1][u]];
    }

    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        numChild[u] += numChild[v];
    }
}

int getPar(int u, int h) {
    for (int i = 0; i < LOG; i++) {
        if (h >> i & 1) {
            u = par[i][u];
        }
    }
    return u;
}

int lca(int u, int v) {
    if (lv[u] < lv[v]) swap(u, v);
    int h = lv[u] - lv[v];
    u = getPar(u, h);
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
        if (par[i][u] != par[i][v]) {
            u = par[i][u];
            v = par[i][v];
        }
    }
    return par[0][u];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        cout << "Case #" << test << ":\n";
        cin >> n >> q >> r;

        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(1, 0);

        while (q--) {
            int s, u;
            cin >> s >> u;
            if (s == 0) {
                r = u;
            } else {
                if (u == r) cout << n << '\n';
                else {
                    int w = lca(u, r);
                    if (w == u) {
                        int v = getPar(r, lv[r] - lv[u] - 1);
                        cout << n - numChild[v] << '\n';
                    } else cout << numChild[u] << '\n';
                }
            }
        }
    }
    return 0;
}