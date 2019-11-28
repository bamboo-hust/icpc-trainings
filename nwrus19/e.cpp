#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
const int LOG = 20;

vector<int> a[N];
int par[LOG][N];
int depth[N];
int tin[N];
int n, m;

int timestamp;
void dfs(int u, int p = 0) {
    tin[u] = ++timestamp;
    par[0][u] = p;
    if (p) {
        a[u].erase(find(begin(a[u]), end(a[u]), p));
    }
    for (int v : a[u]) {
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

int jump(int v, int h) {
    for (int i = LOG - 1; i >= 0; --i) {
        if (h >= (1 << i)) {
            h -= 1 << i;
            v = par[i][v];
        }
    }
    return v;
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    v = jump(v, depth[v] - depth[u]);
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; --i) {
        if (par[i][u] != par[i][v]) {
            u = par[i][u];
            v = par[i][v];
        }
    }
    return par[0][u];
}

int get_dist(int u, int v) {
    int p = lca(u, v);
    int dist = depth[u] + depth[v] - 2 * depth[p];
    return dist;
}

int middle(int u, int v) {
    int dist = get_dist(u, v);
    if (dist % 2) return -1;
    dist /= 2;
    if (depth[u] > depth[v]) {
        return jump(u, dist);
    }
    return jump(v, dist);
}

int get_farthest(int u, const vector<int> &c) {
    int res = u;
    for (int v : c) {
        if (get_dist(u, v) > get_dist(u, res)) {
            res = v;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs(1);

    for (int i = 1; i < LOG; ++i) {
        for (int u = 1; u <= n; ++u) {
            par[i][u] = par[i - 1][par[i - 1][u]];
        }
    }

    vector<int> c(m);
    for (int i = 0; i < m; ++i) {
        cin >> c[i];
    }
    sort(begin(c), end(c), [&] (int u, int v) {return tin[u] < tin[v];});

    if (m == 1) {
        cout << "YES" << endl;
        cout << c[0] << endl;
        return 0;
    }

    int to = get_farthest(c[0], c);
    int to2 = get_farthest(to, c);

    int u = middle(to, to2);
    if (u == -1) {
        cout << "NO\n";
        return 0;
    }

    for (int v : c) {
        if (get_dist(v, u) != get_dist(u, c[0])) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES" << endl;
    cout << u << endl;

    return 0;
}