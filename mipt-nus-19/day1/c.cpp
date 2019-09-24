#include <bits/stdc++.h>

using namespace std;

const int N = 110;
const int INF = 2e9;
const int V = 1e5;

int n, m;
char s[N][N];

struct Flow {
    int n, s, t, cnt;
    int to[V], c[V], f[V];
    int h[V];
    int cur[V];
    vector<int> adj[V];
    Flow(int n, int s, int t) : n(n), s(s), t(t) {
        cnt = 0;
    }
    void addEdge(int u, int v, int _c) {
        //cerr << "addEdge " << u << ' ' << v << endl;
        f[cnt] = 0, to[cnt] = v, c[cnt] = _c;
        adj[u].push_back(cnt++);
        f[cnt] = 0, to[cnt] = u, c[cnt] = 0;
        adj[v].push_back(cnt++);
    }
    bool bfs() {
        for (int i = 0; i < n; i++) {
            h[i] = -1;
        }
        h[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : adj[u]) {
                int v = to[id];
                if (f[id] < c[id] && h[v] == -1) {
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
            for (int i = 0; i < n; i++) cur[i] = 0;
            while (1) {
                int foo = dfs(s, INF);
                if (foo) res += foo;
                else break;
            }
        }
        return res;
    }
};

int getVal(int u, int v) {
    return (u - 1) * m + v;
}

int res[N][N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (s[i] + 1);
    }

    Flow f(n * m + 2, 0, n * m + 1);

    auto addEdge = [&](int u, int v, int x, int y) {
        if ((u + v) % 2 == 1) {
            swap(u, x);
            swap(v, y);
        }
        int foo = getVal(u, v);
        int bar = getVal(x, y);
        f.addEdge(foo, bar, 1);
    };

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if ((i + j) % 2 == 0) f.addEdge(f.s, getVal(i, j), 1);
            else f.addEdge(getVal(i, j), f.t, 1);
        }
    }
    auto inside = [](int u, int v) {
        return u >= 1 && u <= n && v >= 1 && v <= m;
    };
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == 'L') continue;
            if (inside(i + 1, j) && s[i + 1][j] == 'F') {
                addEdge(i, j, i + 1, j);
            }
            if (inside(i, j + 1) && s[i][j + 1] == 'F') {
                addEdge(i, j, i, j + 1);
            }
        }
    }
    int foo = f.maxFlow();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == 'L') continue;
            int id = getVal(i, j);
            int verdict = f.h[id] == -1;
            //cerr << i << ' ' << j << ' ' << verdict << endl;
            if (((i + j) % 2 == 0) ^ verdict) {
                res[i][j] = 1;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == 'L') cout << 'L';
            else if (res[i][j]) cout << 'B';
            else cout << 'F';
        }
        cout << '\n';
    }
    return 0;   
}