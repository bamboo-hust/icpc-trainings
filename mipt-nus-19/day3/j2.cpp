#include <bits/stdc++.h>

using namespace std;

const int N = 10010;
const int LOG = 15;

int n, m;
int w[N];
vector<int> adj[N];
int par[LOG][N];
int lv[N];

void dfs(int u, int p) {
    par[0][u] = p;
    for (int i = 1; i < LOG; i++) par[i][u] = par[i - 1][par[i - 1][u]];
    lv[u] = lv[p] + 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
}

int getPar(int u, int h) {
    for (int i = 0; i < LOG; i++) {
        if (h >> i & 1) u = par[i][u];
    }
    return u;
}

int lca(int u, int v) {
    if (lv[u] < lv[v]) swap(u, v);
    u = getPar(u, lv[u] - lv[v]);
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
        if (par[i][u] != par[i][v]) {
            u = par[i][u];
            v = par[i][v];
        }
    }
    return par[0][u];
}

const int INF = 2e9;
const int V = 1e6;

struct Flow {
    vector<int> adj[V];
    int to[V], f[V], c[V], cur[V];
    int n, s, t, cnt;
    int h[V];
    Flow(int n, int s, int t) : n(n), s(s), t(t) {
        cnt = 0;
    }
    void addEdge(int u, int v, int _c) {
        to[cnt] = v, f[cnt] = 0, c[cnt] = _c;
        adj[u].push_back(cnt++);
        to[cnt] = u, f[cnt] = 0, c[cnt] = 0;
        adj[v].push_back(cnt++);
    }
    bool bfs() {
        fill(h, h + n, -1);
        h[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : adj[u]) {
                int v = to[id];
                if (h[v] == -1 && f[id] < c[id]) {
                    h[v] = h[u] + 1;
                    q.push(v);
                }
            }
        }
        return h[t] != -1;
    }
    int dfs(int u, int res) {
        if (u == t) return res;
        for (int &i = cur[u]; i < adj[u].size(); i++) {
            int id = adj[u][i];
            int v = to[id];
            if (h[v] == h[u] + 1 && f[id] < c[id]) {
                int foo = dfs(v, min(res, c[id] - f[id]));
                if (foo) {
                    f[id] += foo;
                    f[id ^ 1] -= foo;
                    return foo;
                }
            }
        }
        return 0;
    }
    int maxFlow() {
        int res = 0;
        while (bfs()) {
            fill(cur, cur + n, 0);
            while (1) {
                int foo = dfs(s, INF);
                if (foo) res += foo;
                else break;
            }
        }
        return res;
    }
};

int getNode(int u, int v) {
    return n * u + v;
}

void addEdge(int u, int w, int id, Flow &f) {
    int h = lv[u] - lv[w];
    for (int i = 0; i < LOG; i++) {
        if (h >> i & 1) {
            f.addEdge(getNode(i, u), id, INF);
            u = par[i][u];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    Flow f(n * LOG + 2 + m, 0, n * LOG + m + 1);
    for (int i = 1; i <= n; i++) {
        f.addEdge(f.s, getNode(0, i), w[i]);
        for (int j = 1; j < LOG; j++) {
            f.addEdge(getNode(j - 1, i), getNode(j, i), INF);
            int u = par[j - 1][i];
            if (u) f.addEdge(getNode(j - 1, u), getNode(j, i), INF);
        }
    }
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        f.addEdge(n * LOG + i, f.t, c);
        int w = lca(a, b);
        addEdge(a, w, n * LOG + i, f);
        addEdge(b, w, n * LOG + i, f);
        f.addEdge(getNode(0, w), n * LOG + i, INF);
    }
    cout << f.maxFlow() << endl;
    return 0;
}