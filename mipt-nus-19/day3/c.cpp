#include <bits/stdc++.h>

using namespace std;

const int N = 200256;
const int INF = 2e9 + 9;

vector< pair<int, int> > a[N];
int V[N];
int n, m, k;

uint32_t d[N];
int id[N];

pair<uint32_t, int> res[N];

void dijkstra() {
    set< pair<int, int> > S;
    for (int i = 1; i <= n; ++i) {
        d[i] = INF;
        id[i] = 0;
    }
    for (int i = 1; i <= k; ++i) {
        d[V[i]] = 0;
        id[V[i]] = V[i];
        S.insert(make_pair(0, V[i]));
    }
    while (!S.empty()) {
        int u = S.begin()->second;
        S.erase(S.begin());
        for (auto e : a[u]) {
            int v = e.first;
            int c = e.second;
            if (d[v] > d[u] + c) {
                if (d[v] != INF) {
                    S.erase(make_pair(d[v], v));
                }
                d[v] = d[u] + c;
                id[v] = id[u];
                S.insert(make_pair(d[v], v));
            } else if (d[v] == d[u] + c) {
                id[v] = min(id[v], id[u]);
                //res[id[v]] = min(res[id[v]], make_pair(d[v] + d[v], id[u]));
                //res[id[u]] = min(res[id[u]], make_pair(d[v] + d[v], id[v]));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        a[u].push_back(make_pair(v, c));
        a[v].push_back(make_pair(u, c));
    }
    for (int i = 1; i <= k; ++i) {
        cin >> V[i];
    }
    dijkstra();
    for (int i = 1; i <= n; ++i) {
        res[i] = make_pair(INF, 0);
    }
    for (int u = 1; u <= n; ++u) {
        for (auto e : a[u]) {
            int v = e.first;
            int c = e.second;
            if (id[u] != id[v]) {
                res[id[u]] = min(res[id[u]], make_pair(d[u] + d[v] + c, id[v]));
                res[id[v]] = min(res[id[v]], make_pair(d[u] + d[v] + c, id[u]));
            }
        }
    }
    for (int i = 1; i <= k; ++i) {
        cout << res[V[i]].second << '\n';
    }
}