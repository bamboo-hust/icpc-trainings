//
// Created by quanglm1998 on 24/09/2019.
//

#include <bits/stdc++.h>

using namespace std;

const int N = 40010;

int n, m;
vector<int> adj[N];
int used[N];

pair<int, int> go(int root) {
    memset(used, 0, sizeof used);
    int p1 = 0, p2 = 0;
    for (int u : adj[root]) {
        if (!used[u]) {
            used[u] = 1;
            p1++;
        }
    }
    used[root] = 1;
    for (int u : adj[root]) {
        for (int v : adj[u]) {
            if (!used[v]) {
                used[v] = 1;
                p2++;
            }
        }
    }
    return {p1, p2};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    pair<int, int> x = go(1);
    pair<int, int> y = go(2);
    int theRest = n - 2 - x.first - x.second - y.first - y.second;
    long long res = x.first + y.first + 1ll * x.first * x.second + 1ll * y.first * y.second + 1ll * x.second * y.second;
    res += 1ll * x.first * (x.first - 1) / 2;
    res += 1ll * y.first * (y.first - 1) / 2;
    res += 1ll * x.second * (x.second - 1) / 2;
    res += 1ll * y.second * (y.second - 1) / 2;
    res += 1ll * theRest * (theRest - 1) / 2;
    res += 1ll * theRest * (x.second + y.second);
    res += 1ll * theRest * max(x.first, y.first);
    cout << res - m << endl;
    return 0;
}