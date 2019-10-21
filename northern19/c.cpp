#include <bits/stdc++.h>

using namespace std;

const int N = 110;

int n, m, p;
int s[N], r[N], id[N], pos[N];

const int V = 1e6;
const long long INF = 1e18;

struct Flow {
    vector<int> adj[V];
    int to[V];
    long long c[V], f[V];
    int n, s, t, cnt;
    int d[V];
    int cur[V];
    void init(int n, int s, int t) {
        this->n = n;
        this->s = s;
        this->t = t;
        cnt = 0;
        for (int i = 0; i < n; i++) adj[i].clear();
    }
    int addEdge(int u, int v, long long _c) {
        to[cnt] = v, c[cnt] = _c, f[cnt] = 0;
        adj[u].push_back(cnt++);
        to[cnt] = u, c[cnt] = 0, f[cnt] = 0;
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
    long long dfs(int u, long long res) {
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
    long long maxFlow() {
        long long res = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++) cur[i] = 0;
            while (1) {
                long long foo = dfs(s, INF);
                if (!foo) break;
                res += foo;
            }
        }
        return res;
    }
} f;

bool check(long long u) {
    f.init(2 + n * m + n, 0, n * m + n + 1);
    for (int i = 1; i <= m; i++) {
        int last = f.s;
        int need = (p - 1) / s[i] + 1;
        for (int j = 1; j <= n; j++) {
            int cur = (i - 1) * n + j;
            f.addEdge(last, cur, (u - r[id[j]] + 1) / need);
            last = cur;
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int id = (i - 1) * n + pos[j];
            f.addEdge(id, n * m + j, 1);
        }
    }
    for (int i = 1; i <= n; i++) {
        f.addEdge(n * m + i, f.t, 1);
    }
    return f.maxFlow() == n;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> m >> n >> p;
    for (int i = 1; i <= m; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) cin >> r[i];
    for (int i = 1; i <= n; i++) id[i] = i;
    sort(id + 1, id + n + 1, [](int u, int v) {
        return r[u] < r[v];
    });
    for (int i = 1; i <= n; i++) pos[id[i]] = i;

    long long low = *max_element(r + 1, r + n + 1) - 1, high = INF;
    while (high - low > 1) {
        long long mid = low + high >> 1;
        if (check(mid)) high = mid;
        else low = mid;
    }
    cout << high << endl;
    return 0;
}