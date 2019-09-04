#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 6;

struct Edge {
    int v, dx, dy;
};

int n, m;
vector<Edge> a[N];
int x[N], y[N];
bool was[N];

void dfs(int u) {
    was[u] = true;
    for (auto e : a[u]) {
        if (was[e.v]) continue;
        x[e.v] = x[u] + e.dx;
        y[e.v] = y[u] + e.dy;
        dfs(e.v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    while (m--) {
        int u, v, dx, dy;
        cin >> u >> v >> dx >> dy;
        a[u].push_back(Edge{v, dx, dy});
        a[v].push_back(Edge{u, -dx, -dy});
    }
    for (int i = 1; i <= n; ++i) if (!was[i]) {
        x[i] = y[i] = 0;
        dfs(i);
    }
    for (int i = 1; i <= n; ++i) {
        cout << x[i] << ' ' << y[i] << '\n';
    }
}