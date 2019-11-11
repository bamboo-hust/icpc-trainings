#include <bits/stdc++.h>

using namespace std;

int const N = 1e5 + 5;
int const NN = 20;

vector < int > a[N];
int par[NN][N], h[N], max_deep[N];



void dfs(int u, int p) {
    max_deep[u] = u;
    for (int v : a[u]) {
        if (v == p) {
            continue;
        }
        h[v] = h[u] + 1;
        dfs(v, u);
        if (h[max_deep[u]] < h[max_deep[v]]) {
            max_deep[u] = max_deep[v];
        }
        par[0][v] = u;
    }
}

int get_lca(int u, int v) {
    if (h[u] < h[v]) {
        swap(u, v);
    }
    int diff = h[u] - h[v];
    for (int j = 0; j < NN; j++) {
        if ((diff >> j) & 1) {
            u = par[j][u];
        }
    }
    if (u == v) {
        return u;
    }

    for (int j = NN - 1; j >= 0; j--) {
        if (par[j][u] != par[j][v]) {
            u = par[j][u];
            v = par[j][v];
        }
    }
    return par[0][u];
}

int get_par(int u, int p) {
    int diff = h[u] - h[p];
    for (int j = 0; j < NN; j++) {
        if ((diff >> j) & 1) {
            u = par[j][u];
        }
    }
    return u;
}

pair < vector < pair < int, int > >, int > get_answer(int c, int d) {
    vector < int > ans;
    if (h[c] > h[d]) {
        swap(c, d);
    }
    int p = get_lca(c, d);
    if (c != p) {
        int dis = h[c] + h[d] - h[par];
        
        if (h[max_deep[c]] - h[c] < dis && h[max_deep[d]] - h[d] < dis) {
            return make_pair(ans, 0);
        }
        if (h[max_deep[c]] - h[c] >= dis) {
            vector < int > move = get_move(max_deep[c], c);
            c = max_deep[c];
            d = get_par(c, dis);
        } else {
            vector < int > move = get_move(max_deep[d], d);
            c = max_deep[d];
            d = get_par(c, dis);
        }
        ans.insert(ans.begin(), move.begin(), move.end());
    } else {

    }


    return make_pair(ans, 0);
}

int main() {
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            a[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            a[u].push_back(v);
            a[v].push_back(u);
        }

        dfs(1, 0);
        for (int j = 1; j < NN; j++) {
            for (int i = 1; i <= n; i++) {
                par[j][i] = par[j - 1][par[j - 1][i]];
            }
        }

        int a, b, c, d;
        cin >> a >> b >> c >> d;
        pair < vector < pair < int, int > >, int > p = get_answer(a, b);
        pair < vector < pair < int, int > >, int > q = get_answer(c, d);
        if (p.second == 0 || q.second == 0) {
            cout << -1 << endl;
            continue;
        }
        
    }
}