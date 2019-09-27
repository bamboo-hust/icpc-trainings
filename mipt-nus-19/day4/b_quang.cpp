//
// Created by quanglm1998 on 24/09/2019.
//

#include <bits/stdc++.h>

using namespace std;

const int N = 1010;
const int INF = 1e9;

struct Data {
    int v, x, id;
};

int n, m;
vector<Data> adj[N];
vector<int> vals;
vector<int> trace[N];

struct Flow {
    int n, s, t, cnt;
    vector<int> h, cur, f, c, to;
    vector<vector<int>> adj;
    Flow(int n, int s, int t) : n(n), s(s), t(t) {
        cnt = 0;
        h.resize(n);
        cur.resize(n);
        adj.resize(n);
    }
    int addEdge(int u, int v, int _c) {
        adj[u].push_back(to.size());
        to.push_back(v);
        f.push_back(0);
        c.push_back(_c);
        adj[v].push_back(to.size());
        to.push_back(u);
        f.push_back(0);
        c.push_back(0);
        return to.size() - 2;
    }
    bool bfs() {
        fill(h.begin(), h.end(), -1);
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
            if (f[id] < c[id] && h[v] == h[u] + 1) {
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
            fill(cur.begin(), cur.end(), 0);
            while (1) {
                int foo = dfs(s, INF);
                if (foo) res += foo;
                else break;
            }
        }
        return res;
    }
};

bool check(int lim) {
    Flow f(n + m + 2, 0, n + m + 1);
    for (int i = 1; i <= n; i++) {
        f.addEdge(f.s, i, adj[i].size() / 2);
    }
    for (int i = 1; i <= m; i++) {
        f.addEdge(i + m, f.t, 1);
    }
    for (int i = 1; i <= n; i++) {
        fill(trace[i].begin(), trace[i].end(), -1);
        for (int j = 0; j < adj[i].size(); j++) {
            Data u = adj[i][j];
            if (u.v <= vals[lim]) {
                trace[i][j] = f.addEdge(i, n + u.id, 1);
            }
        }
    }
    int now = f.maxFlow();
    return now == m;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        adj[u].push_back({v, x, i});
        adj[v].push_back({u, y, i});
        vals.push_back(x);
        vals.push_back(y);
    }

    int foundOdd = 0;
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() % 2) {
            foundOdd = 1;
        }
        trace[i].resize(adj[i].size());
    }
    if (foundOdd) return (cout << "NIE\n", 0);

    sort(vals.begin(), vals.end());
    int low = -1, high = vals.size();
    while (high - low > 1) {
        int mid = low + high >> 1;
        if (check(mid)) low = mid;
        else high = mid;
    }
    cout << vals[low] << endl;
    return 0;
}