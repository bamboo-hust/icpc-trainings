//
// Created by quanglm1998 on 26/09/2019.
//

#include <bits/stdc++.h>

using namespace std;

const int N = 300010;
const int MOD = 998244353;

inline int add(int u, int v) {
    return (u += v) >= MOD ? u - MOD : u;
}

inline int mul(int u, int v) {
    return (long long)u * v % MOD;
}

int n, q;
pair<int, int> a[N];
vector<int> ls[N], val[N];
map<int, int> query[N];
int root[N];

int getRoot(int u) {
    return root[u] ? root[u] = getRoot(root[u]) : u;
}

void unite(int u, int v, int edgeId) {
    u = getRoot(u);
    v = getRoot(v);
    if (query[u].size() > query[v].size()) swap(u, v);
    for (auto now : query[u]) {
        if (query[v].count(now.first)) {
            int x = now.second;
            int y = query[v][now.first];
            val[now.first][x] = min(val[now.first][x], edgeId);
            val[now.first][y] = min(val[now.first][y], edgeId);
        } else {
            query[v][now.first] = now.second;
        }
    }
    root[u] = v;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int k;
        cin >> k;
        ls[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> ls[i][j];
            query[ls[i][j]][i] = j;
        }
        val[i].resize(k);
        for (int &u : val[i]) u = n;
    }
    for (int i = 1; i < n; i++) {
        unite(a[i].first, a[i].second, i);
    }
    for (int i = 1; i <= q; i++) {
        int res = 1;
        for (int u : val[i]) res = mul(res, u);
        cout << res << '\n';
    }
    return 0;
}