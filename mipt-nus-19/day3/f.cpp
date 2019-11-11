#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, q;
map<pair<int, int>, int> edgeToId;
map<int, int> posInList[N];
int numEdge;
vector<int> adj[N];
vector<int> faceId[N];
int numFace;
set<int> setAdj[N];
int compId[N];

int getEdgeId(int u, int v) {
    if (u > v) swap(u, v);
    return edgeToId.count({u, v}) ? edgeToId[{u, v}] : -1;
}

void addEdge(int u, int v) {
    if (u > v) swap(u, v);
    if (getEdgeId(u, v) == -1) edgeToId[{u, v}] = ++numEdge;
}

void go(int u, int id) {
    int root = u;
    int rootId = id;
    while (1) {
        faceId[u][id] = numFace;
        int v = adj[u][id];
        int idV = posInList[v][u];
        idV = (idV + 1) % adj[v].size();
        u = v;
        id = idV;
        if (u == root && id == rootId) break;
    }
}

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
        return 1;
    }
} dsu;

int used[N];
int dfsCnt;

int findNext(int u, set<int>::iterator &it, queue<int> &q) {
    if (it == setAdj[u].end()) {
        q.pop();
        if (q.empty()) return -1;
        u = q.front();
        it = setAdj[u].begin();
        return findNext(u, it, q);
    } else {
        int v = *it;
        it++;
        if (used[v] == dfsCnt) return findNext(u, it, q);
        used[v] = dfsCnt;
        return v;
    }
}

int getSmallerRoot(int u, int v) {
    queue<int> qU, qV;
    used[u] = used[v] = dfsCnt;
    qU.push(u);
    qV.push(v);
    auto itU = setAdj[u].begin();
    auto itV = setAdj[v].begin();
    while (1) {
        int nextU = findNext(u, itU, qV);
        if (nextU == -1) return u;
        int nextV = findNext(v, itV, qV);
        if (nextV == -1) return v;
    }
    assert(1 == 2);
}

void splitComp(int u, int v, int numComp) { 
    dfsCnt++;
    int w = getSmallerRoot(u, v);
    queue<int> q;
    q.push(w);
    compId[w] = numComp;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : setAdj[u]) {
            if (compId[v] == numComp) continue;
            compId[v] = numComp;
            q.push(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int u;
            cin >> u;
            adj[i].push_back(u);
            setAdj[i].insert(u);
            addEdge(i, u);
            posInList[i][u] = j;
        }
        faceId[i].resize(k);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            if (!faceId[i][j]) {
                numFace++;
                go(i, j);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        compId[i] = 1;
    }

    int numComp = 1;
    int last = 0;
    while (q--) {
        char op;
        int a, b;
        cin >> op >> a >> b;
        a ^= last;
        b ^= last;
        if (op == '-') {
            int u = faceId[a][posInList[a][b]];
            int v = faceId[b][posInList[b][a]];
            setAdj[a].erase(b);
            setAdj[b].erase(a);
            if (!dsu.unite(u, v)) {
                numComp++;
                splitComp(a, b, numComp);
            }
            last = numComp;
            cout << last << '\n';
        } else {
            last = (compId[a] == compId[b]);
            cout << last << '\n';
        }
    }
    return 0;   
}