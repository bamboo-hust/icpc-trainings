#include <bits/stdc++.h>

using namespace std;
#define int long long

const int N = 1500010;
const long long INF = (1ll << 60);

inline long long sqr(long long u) {
    if (u >= 2e9) return u;
    return 1ll * u * u;
}

int n, m, k, q;
pair<int, int> a[N];

struct Edge {
    int u, v, l;
} e[N];

vector<pair<int, long long>> changes[N];
pair<int, int> queries[N];
int root[N];
vector<int> breakEvents[N];
int low[N], high[N];

struct Node {
    long long minVal, maxVal;
    int l, r;
    int lChild, rChild;

    void init(const pair<int, long long> &u) {
        l = r = u.first;
        minVal = maxVal = u.second;
    }
} t[N << 2];
int cntNode;

void pull(int node) {
    int lChild = t[node].lChild;
    int rChild = t[node].rChild;
    t[node].l = t[lChild].l;
    t[node].r = t[rChild].r;
    t[node].minVal = min(t[lChild].minVal, t[rChild].minVal);
    t[node].maxVal = max(t[lChild].maxVal, t[rChild].maxVal);
}

int init(int l, int r, const vector<pair<int, long long>> &changes) {
    int curNode = cntNode++;
    if (l < r) {
        int m = l + r >> 1;
        t[curNode].lChild = init(l, m, changes);
        t[curNode].rChild = init(m + 1, r, changes);
        pull(curNode);
    } else {
        t[curNode].init(changes[l]);     
    }
    return curNode;
}

bool canBreak(Edge &e, long long z, Node &node) {
    int u = e.u, v = e.v, l = e.l;
    long long foo = sqr(a[u].first - a[v].first) + sqr(a[u].second - a[v].second);
    if (foo + sqr(z - node.minVal) > 1ll * l * l) return 1;
    if (foo + sqr(z - node.maxVal) > 1ll * l * l) return 1;
    return 0;
}

int get(int node, int x, int y, Edge &e, long long z) {
    if (x > t[node].r || y < t[node].l) return k + 1;
    if (!canBreak(e, z, t[node])) return k + 1;
    if (t[node].l == t[node].r) return t[node].l;
    int lChild = t[node].lChild;
    int rChild = t[node].rChild;
    int p1 = get(lChild, x, y, e, z);
    if (p1 <= k) return p1;
    return get(rChild, x, y, e, z);
}

int getBreakTime(Edge &e, int v, long long z, int l, int r) {
    int oldL = l;
    l = upper_bound(changes[v].begin(), changes[v].end(), make_pair(l + 1, -INF)) - changes[v].begin() - 1;
    l = changes[v][l].first;
    int res = get(root[v], l, r, e, z);
    return max(oldL, res);
}

struct DSU {
    int root[N];

    void init() {
        for (int i = 1; i <= n; i++) {
            root[i] = i;
        }
    }

    int getRoot(int u) {
        return root[u] == u ? u : root[u] = getRoot(root[u]);
    }

    bool unite(int u, int v) {
        u = getRoot(u);
        v = getRoot(v);
        if (u == v) return 0;
        root[u] = v;
        return 1;
    }
} dsu;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        
        //init
        for (int i = 1; i <= n; i++) {
            changes[i].clear();
            changes[i].push_back({0, 0ll});
        }
        cntNode = 0;

        for (int i = 1; i <= n; i++) {
            cin >> a[i].first >> a[i].second;
        }
        cin >> m;
        for (int i = 1; i <= m; i++) {
            cin >> e[i].u >> e[i].v >> e[i].l;
        }
        cin >> k;

        for (int i = 1; i <= k + 1; i++) {
            breakEvents[i].clear();
        }

        for (int i = 1; i <= k; i++) {
            int v, h;
            cin >> v >> h;
            changes[v].push_back({i, changes[v].back().second + h});
        }

        cin >> q;
        for (int i = 1; i <= q; i++) {
            cin >> queries[i].first >> queries[i].second;
        }

        for (int i = 1; i <= n; i++) {
            root[i] = init(0, changes[i].size() - 1, changes[i]);
        }

        // for (int i = 1; i <= n; i++) {
        //     cout << "in " << i << endl;
        //     for (auto v : changes[i]) cout << v.first << ' ' << v.second << endl;
        // }

        for (int i = 1; i <= m; i++) {
            int &u = e[i].u;
            int &v = e[i].v;
            if (changes[u].size() > changes[v].size()) swap(e[i].u, e[i].v);
            int breakTime = k + 1;
            for (int j = 0; j + 1 < changes[u].size(); j++) {
                breakTime = min(breakTime, getBreakTime(e[i], v, changes[u][j].second, changes[u][j].first, changes[u][j + 1].first - 1));
            }
            breakTime = min(breakTime, getBreakTime(e[i], v, changes[u].back().second, changes[u].back().first, k));
            breakEvents[breakTime].push_back(i);
        }
        for (int i = 1; i <= q; i++) {
            low[i] = 0;
            high[i] = k + 2;
        }
        while (1) {
            vector<pair<int, int>> ls;
            int found = 0;
            for (int i = 1; i <= q; i++) {
                if (low[i] + 1 < high[i]) {
                    found = 1;
                    int mid = low[i] + high[i] >> 1;
                    ls.push_back({mid, i});
                }
            }
            if (!found) break;
            sort(ls.rbegin(), ls.rend());
            int cur = 0;
            dsu.init();
            for (int i = k + 1; i >= 1; i--) {
                for (int val : breakEvents[i]) {
                    dsu.unite(e[val].u, e[val].v);
                }

                while (cur < ls.size() && ls[cur].first == i) {
                    int id = ls[cur].second;
                    int u = queries[id].first;
                    int v = queries[id].second;
                    if (dsu.getRoot(u) == dsu.getRoot(v)) {
                        low[id] = i;
                    } else {
                        high[id] = i;
                    }
                    cur++;
                }
            }
        }
        for (int i = 1; i <= q; i++) {
            if (low[i] > k) cout << -1 << '\n';
            else cout << low[i] << '\n';
        }
    }
    return 0;
}