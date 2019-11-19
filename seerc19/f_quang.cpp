#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
vector<int> adj[N];

int dfs(int u, int p) {
    int res = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        res += dfs(v, u);
    }
    if (res) res--;
    else res++;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v); adj[v].push_back(u);
    }
    cout << (dfs(1, 0) ? "Alice" : "Bob") << endl;
    return 0;
}