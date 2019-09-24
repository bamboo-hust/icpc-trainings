#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int INF = 1e9 + 100;

int n, t;
int d[N], w[N], id[N];
int par[N], lv[N];
int numChild[N];
vector<int> adj[N];
int HLDLs[N], posInHLD[N], cntHLD, top[N];

void dfsInit(int u, int p) {
    numChild[u] = 1;
    par[u] = p;
    for (int v : adj[u]) {
        lv[v] = lv[u] + 1;
        dfsInit(v, u);
        numChild[u] += numChild[v];
    }
}

void dfsBuildHLD(int u, int last) {
    HLDLs[cntHLD] = u;
    posInHLD[u] = cntHLD;
    cntHLD++;
    top[u] = last;
    int biggestChild = -1;
    for (int v : adj[u]) {
        if (biggestChild == -1 || numChild[biggestChild] < numChild[v]) biggestChild = v;
    }
    if (biggestChild != -1) dfsBuildHLD(biggestChild, last);
    for (int v : adj[u]) {
        if (v != biggestChild) dfsBuildHLD(v, v);
    }
}

struct IT {
    int t[N << 2];
    int del[N << 2];

    void init(int node, int l, int r) {
        if (l == r) {
            int id = HLDLs[l];
            t[node] = w[id];
            del[node] = 0;
            return;
        }
        int m = l + r >> 1;
        init(node << 1, l, m);
        init(node << 1 | 1, m + 1, r);
        t[node] = min(t[node << 1], t[node << 1 | 1]);
        del[node] = 0;
    }

    void update(int node, int l, int r, int x, int y, int delta) {
        if (x > r || y < l) return;
        if (x <= l && r <= y) {
            t[node] -= delta;
            del[node] += delta;
            return;
        }
        int m = l + r >> 1;
        update(node << 1, l, m, x, y, delta);
        update(node << 1 | 1, m + 1, r, x, y, delta);
        t[node] = min(t[node << 1], t[node << 1 | 1]) - del[node];
    }

    int get(int node, int l, int r, int x, int y) {
        if (x > r || y < l) return INF;
        if (x <= l && r <= y) return t[node];
        int m = l + r >> 1;
        int p1 = get(node << 1, l, m, x, y);
        int p2 = get(node << 1 | 1, m + 1, r, x, y);
        return min(p1, p2) - del[node];
    }
} it;

int getMinToRoot(int u) {
    int res = INF;
    while (u != -1) {
        int v = top[u];
        res = min(res, it.get(1, 0, n, posInHLD[v], posInHLD[u]));
        u = par[v];
    }
    return res;
}

void updateToRoot(int u, int delta) {
    while (u != -1) {
        int v = top[u];
        it.update(1, 0, n, posInHLD[v], posInHLD[u], delta);
        u = par[v];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> t;
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> d[i] >> p >> w[i];
        id[i] = i;
        adj[p].push_back(i);
    }
    w[0] = INF;
    sort(id + 1, id + n + 1, [](int u, int v) {
        return d[u] > d[v];
    });
    dfsInit(0, -1);
    dfsBuildHLD(0, 0);
    it.init(1, 0, n);
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        int u = id[i];
        int now = getMinToRoot(u);
        now = min(now, t);
        t -= now;
        updateToRoot(u, now);
        res += 1ll * now * d[u];
    }
    cout << res << endl;
    return 0;       
}