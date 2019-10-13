//
// Created by lad on 9/23/19.
//

#include <bits/stdc++.h>

using namespace std;

const int N = 10010;

int n, m;
int w[N];
int lv[N], par[N], numChild[N];
vector<int> adj[N];

int cntHLD, posInHLD[N], lsHLD[N], top[N];

void dfsInit(int u, int p) {
    numChild[u] = 1;
    par[u] = p;
    lv[u] = lv[p] + 1;

    for (int v : adj[u]) {
        if (v == p) continue;
        dfsInit(v, u);
        numChild[u] += numChild[v];
    }
}

void dfsBuildHLD(int u, int p, int last) {
    top[u] = last;
    lsHLD[++cntHLD] = u;
    posInHLD[u] = cntHLD;
    int bestChild = -1;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (bestChild == -1 || numChild[bestChild] < numChild[v]) bestChild = v;
    }

    if (bestChild != -1) dfsBuildHLD(bestChild, u, last);
    for (int v : adj[u]) {
        if (v == p || v == bestChild) continue;
        dfsBuildHLD(v, u, v);
    }
}

const long long INF = (1ll << 60);
const int V = 6e6;

struct Flow {
    vector<int> adj[V];
    vector<int> to, c, f;
    int n, s, t, cnt;
    int d[V];
    int cur[V];
    Flow(int n, int s, int t) {
        this->n = n;
        this->s = s;
        this->t = t;
        cnt = 0;
    }
    int addEdge(int u, int v, int _c) {
        to.push_back(v);
        c.push_back(_c);
        f.push_back(0);
        adj[u].push_back(cnt++);
        to.push_back(u);
        c.push_back(0);
        f.push_back(0);
        adj[v].push_back(cnt++);
        return cnt - 2;
    }
    bool bfs() {
        for (int i = 0; i < n; i++) d[i] = -1;
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : adj[u]) {
                int v = to[id];
                if (d[v] == -1 && f[id] < c[id]) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        return d[t] != -1;
    }
    int dfs(int u, int res) {
        if (u == t) return res;
        for (int &it = cur[u]; it < adj[u].size(); it++) {
            int id = adj[u][it];
            int v = to[id];
            if (d[v] == d[u] + 1 && f[id] < c[id]) {
                int foo = dfs(v, min(c[id] - f[id], res));
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
            for (int i = 0; i < n; i++) cur[i] = 0;
            while (1) {
                int foo = dfs(s, INF);
                if (!foo) break;
                res += foo;
            }
        }
        return res;
    }
};

int goCnt(int node, int l, int r) {
    if (l == r) return 1;
    int m = l + r >> 1;
    return goCnt(node << 1, l, m) + goCnt(node << 1 | 1, m + 1, r) + 1;
}

void addFlow(int node, int l, int r, Flow &f) {
    if (l == r) {
        int id = lsHLD[l];
        f.addEdge(f.s, node, w[id]);
        return;
    }
    int m = l + r >> 1;
    addFlow(node << 1, l, m, f);
    addFlow(node << 1 | 1, m + 1, r, f);
    f.addEdge(node << 1,  node, INF);
    f.addEdge(node << 1 | 1, node, INF);
}

void addRange(int node, int l, int r, int x, int y, int id, Flow &f) {
    if (x > r || y < l) return;
    if (x <= l && r <= y) {
        f.addEdge(node, id, INF);
        return;
    }
    int m = l + r >> 1;
    addRange(node << 1, l, m, x, y, id, f);
    addRange(node << 1 | 1, m + 1, r, x, y, id, f);
}

void addHLD(int u, int v, int id, Flow &f) {
    while (top[u] != top[v]) {
        if (lv[top[u]] < lv[top[v]]) swap(u, v);
        int last = top[u];
        addRange(1, 1, n, posInHLD[last], posInHLD[u], id, f);
        u = par[last];
    }
    if (lv[u] < lv[v]) swap(u, v);
    addRange(1, 1, n, posInHLD[v], posInHLD[u], id, f);
}

int32_t main() {
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
    dfsInit(1, 0);
    dfsBuildHLD(1, 0, 1);

    int cnt = goCnt(1, 1, n);
    Flow f(2 + cnt + m, 0, cnt + m + 1);
    addFlow(1, 1, n, f);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        f.addEdge(cnt + i, f.t, c);
        addHLD(a, b, cnt + i, f);
    }
    cout << f.maxFlow() << endl;
    return 0;
}