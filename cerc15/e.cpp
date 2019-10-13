//
// Created by lad on 10/3/19.
//

#include <bits/stdc++.h>

using  namespace std;

const int N = 300010;

int n, m, q;
int num0, num1, num2;
int circle;
int deg[N];

struct Edge {
    int u, v, w;
    bool operator < (const Edge &u) const {
        return w < u.w;
    }
} e[N];

pair<int, int> queries[N];

struct DSU {
    int root[N], numberOfLeaves[N], edges[N];
    void init() {
        fill(root + 1, root + n + 1, -1);
        fill(numberOfLeaves + 1, numberOfLeaves + n + 1, 0);
        fill(edges + 1, edges + n + 1, 0);
    }

    int getRoot(int u) {
        return root[u] > 0 ? root[u] = getRoot(root[u]) : u;
    }

    int get(int u) {
        return (numberOfLeaves[u] == 0) && (edges[u] == -root[u]);
    }

    void join(int u, int v) {
        int uu = getRoot(u);
        int vv = getRoot(v);
        if (uu == vv) {
            circle -= get(uu);
            edges[uu]++;
            numberOfLeaves[uu] -= (deg[u] == 1);
            numberOfLeaves[vv] -= (deg[v] == 1);
            numberOfLeaves[uu] += (deg[u] == 0);
            numberOfLeaves[vv] += (deg[v] == 0);
            circle += get(uu);
        } else {
            circle -= get(uu);
            circle -= get(vv);
            numberOfLeaves[uu] -= (deg[u] == 1);
            numberOfLeaves[vv] -= (deg[v] == 1);
            numberOfLeaves[uu] += (deg[u] == 0);
            numberOfLeaves[vv] += (deg[v] == 0);
            root[uu] += root[vv];
            root[vv] = uu;
            numberOfLeaves[uu] += numberOfLeaves[vv];
            edges[uu] += edges[vv];
            edges[uu]++;
            circle += get(uu);
        }
//        cerr << "jon " << u << ' ' << v << ' ' << numberOfLeaves[uu] << ' '<<  << endl;
    }
} dsu;

void up(int u) {
    if (deg[u] == 0) {
        num0--;
        num1++;
    } else if (deg[u] == 1) {
        num1--;
        num2++;
    } else if (deg[u] == 2) {
        num2--;
    }
}

void add(int u, int v) {
    up(u), up(v);
    dsu.join(u, v);
    deg[u]++;
    deg[v]++;
}

pair<int, int> res[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    memset(deg, 0, sizeof deg);
    num0 = n;
    num1 = num2 = circle = 0;
    for (int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }
    sort(e + 1, e + m + 1);
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> queries[i].first;
        queries[i].second = i;
    }
    sort(queries + 1, queries + q + 1);
    reverse(queries + 1, queries + q + 1);
    reverse(e + 1, e + m + 1);
    dsu.init();
    int cur = 1;
    for (int i = 1; i <= q; i++) {
        while (cur <= m && e[cur].w >= queries[i].first) {
            add(e[cur].u, e[cur].v);
            cur++;
        }
//        cerr << num0 << ' ' << num1 << ' ' << num2 << ' ' << circle << endl;
//        cout << n - num0 - num2 + circle << ' ' << i - num2 + circle << '\n';
        res[queries[i].second] = {n - num0 - num2 + circle, cur - 1 - num2 + circle};
    }
    for (int i = 1; i <= q; i++) cout << res[i].first << ' ' << res[i].second << '\n';
    return 0;
}