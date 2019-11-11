#include <bits/stdc++.h>

using namespace std;


int const N = 1e3 + 5;
int const MAX = 1e9 + 7;

struct Edge {
    int u, v;
    int c;

    bool operator < (const Edge &o) const {
        if (c != o.c) return c < o.c;
        return v < o.v;
    }
};

int a[N][N], d[N][N], in[N], n, m;
int S[N][N];
vector<pair<int, int>> adj[N];
vector<Edge> E;

int cur[N];
int limit[N];
bool was[N];

int get(int u, int v) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i][u] < a[i][v]) {
            cnt++;
        }
    }

    return cnt;
}

void flood(int root, int u) {
    while (cur[u] > limit[u]) {
        --cur[u];
        int v = adj[u][cur[u]].second;
        if (was[v]) continue;
        was[v] = true;
        S[root][v] = adj[u][cur[u]].first;
        flood(root, v);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if (a[i][j] == 0) {
                a[i][j] = MAX;
            }
        }
    }

    for (int u = 1; u <= m; u++) {
        for (int v = 1; v <= m; v++) {
            d[u][v] = get(u, v);
        }
    }


    for (int u = 1; u <= m; u++) {
        for (int v = 1; v <= m; v++) {
            if (d[u][v] > d[v][u]) {
                adj[u].push_back({d[u][v], v});
                E.push_back(Edge{u, v, d[u][v]});
            }
        }
        sort(rbegin(adj[u]), rend(adj[u]));
    }
/*
    sort(rbegin(E), rend(E));
    for (int u = 1; u <= m; ++u) {
        for (int v = 1; v <= m; ++v) {
            limit[v] = adj[v].size();
            cur[v] = adj[v].size();
            was[v] = false;
        }
        was[u] = true;
        for (int eid = E.size() - 1; eid >= 0; --eid) {
            --limit[E[eid].u];
            if (was[E[eid].u]) flood(E[eid].u, E[eid].u);
        }
    }
*/
    for (int k = 1; k <= m; ++k) {
        for (int u = 1; u <= m; ++u) {
            for (int v = 1; v <= m; ++v) {
                d[u][v] = max(d[u][v], min(d[u][k], d[k][v]));
            }
        }
    }
//    for (int u = 1; u <= m; ++u) {
//        for (int v = 1; v <= m; ++v) {
//            cerr << S[u][v] << ' ';
//        }
//        cerr << endl;
//    }

    bool already = false;
    for (int x = 1; x <= m; ++x) {
        bool exist = false;
        for (int y = 1; y <= m; ++y) {
            if (d[x][y] < d[y][x]) {
                exist = true;
                break;
            }
        }
        if (!exist) {
            if (already) cout << ' ';
            cout << x;
            already = true;
        }
    }
    cout << endl;
}