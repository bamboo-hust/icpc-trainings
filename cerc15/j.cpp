//
// Created by lad on 10/3/19.
//

#include <bits/stdc++.h>

using namespace std;

const int N = 3010;
const int MOD = 1000000007;
const int BASE = 10007;

inline int add(int u, int v) {
    return (u += v) >= MOD ? u - MOD : u;
}

inline int mul(int u, int v) {
    return (long long)u * v % MOD;
}

int n, m;
int low[N], num[N], g[N];
int cntTarjan, cntGroup;
vector<int> stTarjan;
vector<int> ls[N];
int deg[N];
vector<int> adj[N];
int h[N];

void dfs(int u, int p) {
    low[u] = num[u] = ++cntTarjan;
    stTarjan.push_back(u);
    for (int v : adj[u]) {
        if (v == p) continue;
        if (g[v]) continue;
        if (!num[v]) dfs(v, u);
        low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
        cntGroup++;
        while (1) {
            int v = stTarjan.back();
            stTarjan.pop_back();
            g[v] = cntGroup;
            ls[cntGroup].push_back(v);
            if (v == u) break;
        }
    }
}

int lowTemp[N], numTemp[N], cntTemp, cntGroupTemp;
vector<int> stTemp;

bool equal(int u, int v, int x, int y) {
    if (u > v) swap(u, v);
    if (x > y) swap(x, y);
    return u == x && v == y;
}

void go(int u, int p, int x, int y) {
    lowTemp[u] = numTemp[u] = ++cntTemp;
    stTemp.push_back(u);
    for (int v : adj[u]) {
        if (g[v] != g[u]) continue;
        if (v == p || equal(u, v, x, y)) continue;
        if (!lowTemp[v]) go(v, u, x, y);
        lowTemp[u] = min(lowTemp[u], lowTemp[v]);
    }
    if (lowTemp[u] == numTemp[u]) {
        cntGroupTemp++;
        while (1) {
            int v = stTemp.back();
            stTemp.pop_back();
            h[v] = mul(h[v], BASE);
            h[v] = add(h[v], cntGroupTemp);
            if (u == v) break;
        }
    }
}

void solve(int id, int u, int v) {
    for (int x : ls[id]) {
        lowTemp[x] = numTemp[x] = 0;
    }
    cntTemp = cntGroupTemp = 0;
    stTemp.clear();
    go(u, 0, u, v);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (u != v) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (!low[i]) {
            int last = cntGroup;
            dfs(i, 0);
            for (int j = last + 1; j <= cntGroup; j++) {
                for (int k = j + 1; k <= cntGroup; k++) {
                    res += ls[j].size() * ls[k].size();
                }
            }
            for (int j = last + 1; j <= cntGroup; j++) {
                for (int u : ls[j]) {
                    for (int v : adj[u]) {
                        if (g[v] == j) {
                            solve(j, u, v);
                        }
                    }
                }
                for (int x = 0; x < ls[j].size(); x++) {
                    for (int y = x + 1; y < ls[j].size(); y++) {
                        int xx = ls[j][x];
                        int yy = ls[j][y];
                        if (h[xx] == h[yy]) res += 3;
                        else res += 2;
                    }
                }
            }
        }
    }
    cout << res << endl;
    return 0;
}