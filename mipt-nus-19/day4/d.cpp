#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, m, k;
pair<int, int> edges[N];
int used[N];
int delEdge[N];
vector<int> l[N];
int res[N];
int numSrc;

struct DSU {
    int root[N];
    DSU() {
        memset(root, 0, sizeof root);
    }
    int getRoot(int u) {
        return root[u] ? root[u] = getRoot(root[u]) : u;
    }
    int unite(int u, int v) {
        u = getRoot(u);
        v = getRoot(v);
        if (u == v) return 0;
        root[u] = v;
        return v;
    }
} sccId, srcId;

void joinNode(int u, int v) {
    sccId.root[u] = v;
    if (l[v].size() < l[u].size()) l[v].swap(l[u]);
    l[v].insert(l[v].end(), l[u].begin(), l[u].end());
}

void addEdge(int id) {
    int u, v;
    tie(u, v) = edges[id];
    u = sccId.getRoot(u);
    v = sccId.getRoot(v);
    if (srcId.getRoot(v) == v) {
        l[v].push_back(u);
        while (!l[v].empty()) {
            int w = l[v].back();
            w = sccId.getRoot(w);
            if (w == v) {
                l[v].pop_back();
                continue;
            }
            int srcW = srcId.getRoot(w);
            if (srcW == v) {
                l[v].pop_back();
                joinNode(w, v);
                continue;
            }
            numSrc--;
            srcId.root[v] = srcW;
            break;   
        }
    } else {
        l[v].push_back(u);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }
    cin >> k;
    for (int i = 1; i <= k; i++) {
        cin >> delEdge[i];
        used[delEdge[i]] = 1;
    }

    numSrc = n;

    for (int i = 1; i <= m; i++) {
        if (!used[i]) addEdge(i);
    }

    for (int i = k; i > 0; i--) {
        res[i] = numSrc;
        addEdge(delEdge[i]);
    }
    for (int i = 1; i <= k; i++) cout << res[i] << '\n';
    return 0;
}