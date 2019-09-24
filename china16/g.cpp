#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, m;
int c[N];
map<int, int> numberOfColor[N];
int bestColor[N], numberOfBestColor[N];
set<int> s[N];
vector<pair<int, int>> roots[N];
vector<pair<int, int>> res[N];
int root[N];

int getRoot(int u) {
    return root[u] < 0 ? u : root[u] = getRoot(root[u]);
}

struct Edge {
    int u, v, w;
    Edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}

    bool operator < (const Edge &o) const {
        return w < o.w;
    }
} edges[N];

void init() {
    for (int i = 1; i <= n; i++) {
        s[i].clear();
        numberOfColor[i].clear();
        roots[i].clear();
        res[i].clear();
        root[i] = -1;

        bestColor[i] = c[i];
        numberOfBestColor[i] = 1;
        numberOfColor[i][c[i]] = 1;
        s[i].insert(i);
        roots[i].push_back({0, i});
        res[i].push_back({0, c[i]});
    }
}

// u and v currently are roots
void unite(int u, int v, int w) {
    if (s[u].size() > s[v].size()) swap(u, v);
    for (int val : s[u]) {
        roots[val].push_back({w, v});
        int num = ++numberOfColor[v][c[val]];
        if (num == numberOfBestColor[v]) {
            bestColor[v] = min(bestColor[v], c[val]);
        } else if (num > numberOfBestColor[v]) {
            numberOfBestColor[v] = num;
            bestColor[v] = c[val];
        }
        s[v].insert(val);
    }
    res[v].push_back({w, bestColor[v]});
    root[v] += root[u];
    root[u] = v;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    for (int test = 1; test <= tc; test++) {
        cout << "Case #" << test << ":\n";
        cin >> n >> m;


        for (int i = 1; i <= n; i++) {
            cin >> c[i];
        }
        for (int i = 1; i <= m; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            edges[i] = Edge(x, y, z);
        }
        init();
        sort(edges + 1, edges + m + 1);

        for (int i = 1; i <= m; i++) {
            int u, v, w;
            u = edges[i].u;
            v = edges[i].v;
            w = edges[i].w;

            u = getRoot(u);
            v = getRoot(v);
            if (u == v) continue;
            unite(u, v, w);
        }

        int q;
        cin >> q;
        int last = 0;
        while (q--) {
            int x, w;
            cin >> x >> w;
            x ^= last;
            w ^= last;

            int curRootId = lower_bound(roots[x].begin(), roots[x].end(), make_pair(w + 1, -1)) - roots[x].begin() - 1;
            int curRoot = roots[x][curRootId].second;
            int curResId = lower_bound(res[curRoot].begin(), res[curRoot].end(), make_pair(w + 1, -1)) - res[curRoot].begin() - 1;
            int curRes = res[curRoot][curResId].second;
            last = curRes;
            cout << last << '\n';
        }
    }   
    return 0;       
}