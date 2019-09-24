//
// Created by lad on 9/23/19.
//

#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int n, m;
vector<int> adj[N];
int dp[N], deg[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (u == v) continue;
        adj[u].push_back(v);
        deg[v]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!deg[i]) q.push(i);
        dp[i] = 1;
    }
    int res = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        res = max(res, dp[u]);
        for (int v : adj[u]) {
            deg[v]--;
            dp[v] = max(dp[v], dp[u] + 1);
            if (!deg[v]) q.push(v);
        }
    }
    cout << (res == n ? "Yes" : "No") << endl;
    return 0;
}