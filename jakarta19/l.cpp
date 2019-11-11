#include <bits/stdc++.h>

using namespace std;

const int M = 20010;

int n, k;
int a[M];
vector<int> b[M];
vector<int> vals;
int lastWorker[M];
int root[M];
int sz[M];
int c[M];
int inCircle[M];
int used[M];
int numCirle;
vector<int> roads[M];

const int V = 1e5;
const int INF = 2e9;

struct MinCostMaxFlow {
    int n, s, t, cnt;
    int to[V], f[V], c[V], cost[V];
    vector<int> adj[V];
    int h[V], inQueue[V];
    int par[V];

    MinCostMaxFlow(int n, int s, int t) : n(n), s(s), t(t) {
        cnt = 0;
    }
    int addEdge(int u, int v, int _c, int _cost) {
        to[cnt] = v, f[cnt] = 0, c[cnt] = _c, cost[cnt] = _cost;
        adj[u].push_back(cnt++);
        to[cnt] = u, f[cnt] = 0, c[cnt] = 0, cost[cnt] = -_cost;
        adj[v].push_back(cnt++);
        return cnt - 2;
    }
    pair<int, int> maxFlow() {
        int res = 0, minCost = 0;
        while (1) {
            for (int i = 0; i < n; i++) {
                par[i] = -1;
                h[i] = INF;
                inQueue[i] = 0;
            }
            h[s] = 0;
            inQueue[s] = 1;
            queue<int> q;
            q.push(s);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                inQueue[u] = 0;
                for (int id : adj[u]) {
                    int v = to[id];
                    if (h[v] > h[u] + cost[id] && f[id] < c[id]) {
                        h[v] = h[u] + cost[id];
                        par[v] = id;
                        if (!inQueue[v]) {
                            inQueue[v] = 1;
                            q.push(v);
                        }
                    }
                }
            }
            if (par[t] == -1) break;
            int x = t;
            int now = INF;
            while (x != s) {
                int id = par[x];
                now = min(now, c[id] - f[id]);
                x = to[id ^ 1];
            }
            x = t;
            while (x != s) {
                int id = par[x];
                minCost += cost[id] * now;
                f[id] += now;
                f[id ^ 1] -= now;
                x = to[id ^ 1];
            }
            res += now;
        }
        return {res, minCost};
    }
};

void findCircle() {
    memset(used, -1, sizeof used);
    used[1] = 0;
    vector<int> ls;
    ls.push_back(1);
    int last = -1;
    while (1) {
        int u = ls.back();
        int v = a[u];
        if (used[v] == -1) {
            used[v] = ls.size();
            ls.push_back(v);
            continue;
        }
        last = used[v];
        break;
    }
    for (int i = last; i < ls.size(); i++) {
        inCircle[ls[i]] = 1;
        numCirle++;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        int sz;
        cin >> sz;
        b[i].resize(sz);
        for (int &u : b[i]) {
            cin >> u;
            vals.push_back(u);
        }
    }
    for (int i = 1; i <= k; i++) {
        cin >> c[i];
        vals.push_back(c[i]);
    }

    vals.push_back(-1);
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());

    for (int i = 1; i <= n; i++) {
        for (int &u : b[i]) {
            u = lower_bound(vals.begin(), vals.end(), u) - vals.begin();
        }
    }
    for (int i = 1; i <= k; i++) {
        c[i] = lower_bound(vals.begin(), vals.end(), c[i]) - vals.begin();
        if (!lastWorker[c[i]]) {
            lastWorker[c[i]] = i;
        }
        root[i] = lastWorker[c[i]];
        sz[root[i]]++;
    }

    findCircle();

    MinCostMaxFlow f(2 + n + k, 0, 1 + n + k);
    for (int i = 1; i <= n; i++) {
        f.addEdge(f.s, i, 1, inCircle[i]);
        for (int u : b[i]) {
            if (lastWorker[u]) {
                f.addEdge(i, n + lastWorker[u], 1, 0);
            }
        }
    }
    for (int i = 1; i <= k; i++) {
        if (lastWorker[c[i]] == i) {
            f.addEdge(i + n, f.t, sz[i], 0);
        }
    }
    pair<int, int> now = f.maxFlow();
    if (now.first < n - 1) return (cout << -1 << endl, 0);
    if (now.first == n - 1 && now.second == numCirle) return (cout << -1 << endl, 0);

    for (int i = 1; i <= n; i++) {
        for (int id : f.adj[i]) {
            int v = f.to[id];
            if (v == f.s) continue;
            if (f.f[id] == 1) roads[v - n].push_back(i);
        }
    }
    for (int i = 1; i <= k; i++) {
        int u = root[i];
        if (roads[u].empty()) cout << 0 << ' ' << 0 << '\n';
        else {
            int id = roads[u].back();
            roads[u].pop_back();
            cout << id << ' ' << a[id] << '\n';
        }
    }
    return 0;
}