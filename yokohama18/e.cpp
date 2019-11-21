#include <bits/stdc++.h>

using namespace std;

const int N = 110;

int n, m;
int a[N][N], b[N][N];
int del[N];
vector<int> adj[N];
int used[N];
int inDFS[N];

void dfs(int u) {
    inDFS[u] = 1;
    int numChild = 0;
    int deg = 0;
    for (int v : adj[u]) {
        if (inDFS[v]) continue;
        numChild++;
        dfs(v);
        if (!del[v]) {
            deg++;
            b[u][v] = b[v][u] = 1;
        }
    }
    if (numChild == n - 1) {
        cout << -1 << endl;
        exit(0);
    }
    if (deg & 1) del[u] = 1;
}

void solve(int root) {
    vector<int> q;
    q.push_back(root);
    used[root] = 1;
    for (int i = 0; i < q.size(); i++) {
        int u = q[i];
        for (int v : adj[u]) {
            if (!used[v]) {
                used[v] = 1;
                q.push_back(v);
            }
        }
    }
    if (q.size() & 1) {
        cout << -1 << endl;
        exit(0);
    }
    sort(q.begin(), q.end(), [&](int u, int v) { return adj[u].size() > adj[v].size(); });
    root = q[0];
    dfs(root);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        a[u][v] = a[v][u] = 1;
    }
    if (n & 1) {
        int tot = n * (n - 1) / 2;
        cout << tot - m << '\n';
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (!a[i][j]) cout << i << ' ' << j << '\n';
            }
        }
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (!a[i][j]) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            solve(i);
        }
    }
    vector<pair<int, int>> res;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (!a[i][j] && !b[i][j]) {
                res.push_back({i, j});
            }
        }
    }
    cout << res.size() << '\n';
    for (auto u : res) {
        cout << u.first << ' ' << u.second << '\n';
    }
    return 0;
}