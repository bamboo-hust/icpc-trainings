#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;
const int LOG = 20;
const int MOD = 998244353;

struct Edge {
    int u, v;
} E[N];

int head[N], tail[N];
pair<int, int> next_edge[N];
int lab[N];
int pos[N];
int cost[LOG][N];
int n;

int root(int u) {
    if (lab[u] <= 0) return u;
    return lab[u] = root(lab[u]);
}

void join(int u, int v, int e) {
    u = root(u); v = root(v);
    if (u == v) return;
    lab[u] = v;
    next_edge[tail[u]] = make_pair(head[v], e);
    head[v] = head[u];
}

int get_max(int l, int r) {
    if (l > r) swap(l, r);
    --r;
    int k = log2(r - l + 1);
    return max(cost[k][l], cost[k][r - (1 << k) + 1]);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; ++i) cin >> E[i].u >> E[i].v;
    for (int i = 1; i <= n; ++i) head[i] = tail[i] = i;
    for (int i = 1; i < n; ++i) join(E[i].u, E[i].v, i);

    int r = root(1);
    int cur_size = 0;
    for (int i = head[r]; i; ) {
        pos[i] = ++cur_size;
        int e = next_edge[i].second;
        if (!e) break;
        cost[0][cur_size] = e;
        i = next_edge[i].first;
    }

    for (int i = 1; i < LOG; ++i) {
        for (int j = 1; j + (1 << i) <= n; ++j) {
            cost[i][j] = max(cost[i - 1][j], cost[i - 1][j + (1 << i - 1)]);
        }
    }

    int q; cin >> q;
    while (q--) {
        int k; cin >> k;
        vector<int> a(k);
        for (int i = 0; i < k; ++i) cin >> a[i];
        sort(a.begin(), a.end(), [&] (int u, int v) { return pos[u] < pos[v]; });
        int64_t res = 1;
        for (int i = 0; i < k; ++i) {
            int cur = n;
            if (i > 0) {
                cur = min(cur, get_max(pos[a[i - 1]], pos[a[i]]));
            }
            if (i + 1 < k) {
                cur = min(cur, get_max(pos[a[i]], pos[a[i + 1]]));
            }
            res = res * cur % MOD;
        }
        cout << res << '\n';
    }

}