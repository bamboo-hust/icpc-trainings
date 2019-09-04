#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5 + 5;
const long long INF = (long long)1e18;

int n, m, k, s, t;
long long ds[N], dt[N];
vector<pair<int, int> > a[N], r[N];

void dijkstra(vector<pair<int, int> > a[], long long d[], int source) {
    priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > Q;
    for (int i = 1; i <= n; ++i) d[i] = INF;
    d[source] = 0;
    Q.push(make_pair(0LL, source));
    while (!Q.empty()) {
        int u = Q.top().second;
        long long du = Q.top().first;
        Q.pop();
        if (du != d[u]) continue;
        for (int i = 0; i < a[u].size(); ++i) {
            int v = a[u][i].first;
            int c = a[u][i].second;
            if (d[v] > d[u] + c) {
                d[v] = d[u] + c;
                Q.push(make_pair(d[v], v));
            }
        }
    }
}

main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k >> s >> t;
    for (int i = 1; i <= m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        a[u].push_back(make_pair(v, c));
        r[v].push_back(make_pair(u, c));
    }
    dijkstra(a, ds, s);
    dijkstra(r, dt, t);
    long long ans = ds[t];
    for (int i = 1; i <= k; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        ans = min(ans, ds[u] + c + dt[v]);
        ans = min(ans, ds[v] + c + dt[u]);
    }
    if (ans < INF) {
        cout << ans << endl;
    } else {
        cout << "-1\n";
    }
    return 0;
}
