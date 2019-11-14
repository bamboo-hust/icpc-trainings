#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const int INF = (int)1e9 + 10;

int n;
vector<pair<int, int>> adj[N];
bool hasShop[N];
int used[N];
pair<int, int> minDist[N];
int res[N];
bool isDead[N];
int numChild[N];

struct BIT {
    int n;
    int t[N * 2];

    void init(int n) {
        this->n = n;
        fill(t, t + n, 0);
    }

    void add(int x, int v) {
        while (x < n) {
            t[x] += v;
            x += x & -x;
        }
    }

    int get(int x) {
        int res = 0;
        while (x) {
            res += t[x];
            x -= x & -x;
        }
        return res;
    }

    int getBigger(int x) {
        assert(x < n);
        return get(n - 1) - get(x);
    }
} t;

void init() {
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        used[i] = 0;
        res[i] = 0;
        isDead[i] = 0;
    }
}

void dijkstra() {
    set<pair<pair<int, int>, int>> s;
    for (int i = 1; i <= n; i++) {
        minDist[i] = {INF, INF};
        if (hasShop[i]) {
            minDist[i] = {0, i};
            s.insert({minDist[i], i});
        }
    }
    while (!s.empty()) {
        auto now = *s.begin();
        s.erase(s.begin());
        int u = now.second;
        if (used[u]) continue;
        used[u] = 1;
        for (auto v : adj[u]) {
            pair<int, int> cur(minDist[u].first + v.second, minDist[u].second);
            if (cur < minDist[v.first]) {
                minDist[v.first] = cur;
                s.insert({minDist[v.first], v.first});
            }
        }
    }
}

void dfsInitNumChild(int u, int p) {
    numChild[u] = 1;
    for (auto v : adj[u]) {
        if (isDead[v.first]) continue;
        if (v.first == p) continue;
        dfsInitNumChild(v.first, u);
        numChild[u] += numChild[v.first];
    }
}

int dfsFindCentroid(int u, int p, int sz) {
    int found = 0;
    for (auto v : adj[u]) {
        if (isDead[v.first] || v.first == p) continue;
        int now = dfsFindCentroid(v.first, u, sz);
        if (now != -1) return now;
        found |= (numChild[v.first] * 2 > sz);
    }
    found |= (sz > 2 * numChild[u]);
    if (!found) return u;
    return -1;
}

int findCentroid(int u) {
    dfsInitNumChild(u, 0);
    return dfsFindCentroid(u, 0, numChild[u]);
}

vector<pair<int, int>> vals;

void dfsFromRoot(int u, int p, int root, int sumW) {
    if (u != root) {
        vals.push_back({sumW, u});
        vals.push_back({minDist[u].first - sumW, minDist[u].second});
    }
    res[u] += minDist[root] > make_pair(sumW, u);
    if (u != root) res[root] += minDist[u] > make_pair(sumW, root);
    for (auto v : adj[u]) {
        if (isDead[v.first] || v.first == p) continue;
        dfsFromRoot(v.first, u, root, sumW + v.second);
    }
}

int getPos(const pair<int, int> &u) {
    return lower_bound(vals.begin(), vals.end(), u) - vals.begin();
}

void dfsCalc(int u, int p, int sumW) {
    int pos = getPos({sumW, u});
    res[u] += t.getBigger(pos);
    // cout << "get " << u << ' ' << pos << ' ' << t.getBigger(pos) << endl;
    for (auto v : adj[u]) {
        if (isDead[v.first] || v.first == p) continue;
        dfsCalc(v.first, u, sumW + v.second);
    }
}

void dfsUpdate(int u, int p, int sumW) {
    int pos = getPos({minDist[u].first - sumW, minDist[u].second});
    t.add(pos, 1);
    // cout << "add " << u << ' ' << pos << endl;
    for (auto v : adj[u]) {
        if (isDead[v.first] || v.first == p) continue;
        dfsUpdate(v.first, u, sumW + v.second);
    }
}

void dfsCentroid(int u) {
    u = findCentroid(u);
    // cout << "centroid " << u << endl;
    vals.clear();
    vals.push_back({-INF * 2, -INF * 2});
    dfsFromRoot(u, 0, u, 0);
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    t.init(vals.size());
    // for (auto val : vals) cout << val.first << ' ' << val.second << endl;
    //     cout << endl;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].first;
        int w = adj[u][i].second;
        if (isDead[v]) continue;
        dfsCalc(v, u, w);
        dfsUpdate(v, u, w);
    }
    t.init(vals.size());
    for (int i = (int)adj[u].size() - 1; i >= 0; i--) {
        int v = adj[u][i].first;
        int w = adj[u][i].second;
        if (isDead[v]) continue;
        dfsCalc(v, u, w);
        dfsUpdate(v, u, w);
    }

    isDead[u] = 1;
    for (auto v : adj[u]) {
        if (isDead[v.first]) continue;
        dfsCentroid(v.first);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    while (cin >> n) {
        // cout << "n = " << n << endl;
        init();
        for (int i = 1; i < n; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        for (int i = 1; i <= n; i++) {
            cin >> hasShop[i];
        }
        dijkstra();
        dfsCentroid(1);
        // for (int i = 1; i <= n; i++) cout << res[i] << ' ';
        //     cout << endl;
        cout << *max_element(res + 1, res + n + 1) << '\n';
    }
    return 0;
}