#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

struct DAG {
    int n, m;
    vector<int> adj[N];
    vector<int> revAdj[N];
    int deg[N];
    int canWin[N], dp[N];

    void input() {
        cin >> n >> m;
        memset(deg, 0, sizeof deg);
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            revAdj[v].push_back(u);
            deg[u]++;
        }
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (!deg[i]) q.push(i);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            canWin[u] = 0;
            for (int v : adj[u]) {
                canWin[u] |= (!canWin[v]);
            }   
            if (canWin[u]) {
                dp[u] = N;
                for (int v : adj[u]) {
                    if (!canWin[v]) {
                        dp[u] = min(dp[u], dp[v] + 1);
                    }
                }
            } else {
                dp[u] = 0;
                for (int v : adj[u]) {
                    dp[u] = max(dp[u], dp[v] + 1);
                }
            }

            for (int v : revAdj[u]) {
                if (--deg[v] == 0) {
                    q.push(v);
                }
            }
        }
    }
} d1, d2;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    d1.input();
    d2.input();
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (!d1.canWin[u] && !d2.canWin[v]) cout << "second" << '\n';
        else if (d1.canWin[u] && d2.canWin[v]) cout << "first" << '\n';
        else if (d1.canWin[u]) {
            cout << (d1.dp[u] < d2.dp[v] ? "first" : "second") << '\n';
        } else {
            cout << (d2.dp[v] < d1.dp[u] ? "first" : "second") << '\n';
        }
    }
    return 0;
}