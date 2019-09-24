#include <bits/stdc++.h>

using namespace std;

const int N = 2000010;

int n;
vector<int> adj[N];
int canWin[N];
vector<int> res;

void dfsInit(int u) {
    int hasLosingChild = 0;
    for (int v : adj[u]) {
        dfsInit(v);
        hasLosingChild |= (canWin[v] == 0);
    }
    canWin[u] = hasLosingChild;
}

void dfs(int u, int par) {
    int firstLose = adj[u].size();
    int lastLose = -1;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (!canWin[v]) {
            firstLose = min(firstLose, i);
            lastLose = max(lastLose, i);
        }
    }
    if (par & !canWin[u]) {
        res.push_back(u);
    }
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        int hasLose = (par == 0);
        hasLose |= (firstLose < i);
        hasLose |= (lastLose > i);
        dfs(v, hasLose);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int u;
        cin >> u;
        adj[u].push_back(i);
    }
    dfsInit(1);
    dfs(1, 1);
    sort(res.begin(), res.end());
    for (int u : res) cout << u << '\n';
    return 0;
}