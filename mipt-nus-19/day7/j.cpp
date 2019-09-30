//
// Created by lad on 9/28/19.
//

#include <bits/stdc++.h>

using namespace std;

const int V = 2e6;

struct TWOSAT {
    int n;
    int numComp;
    vector<int> adj[V];
    int low[V], num[V], root[V], cntTarjan;
    vector<int> stTarjan;
    int color[V];

    TWOSAT(int n) : n(n) {
        memset(root, -1, sizeof root);
        memset(low, -1, sizeof low);
        memset(num, -1, sizeof num);
        memset(color, -1, sizeof color);
        cntTarjan = 0;
        stTarjan.clear();
    }

    void addEdge(int u, int v) {
        adj[u ^ 1].push_back(v);
        adj[v ^ 1].push_back(u);
    }

    void tarjan(int u) {
        stTarjan.push_back(u);
        num[u] = low[u] = cntTarjan++;
        for (int v : adj[u]) {
            if (root[v] != -1) continue;
            if (low[v] == -1) tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u]) {
            while (1) {
                int v = stTarjan.back();
                stTarjan.pop_back();
                root[v] = numComp;
                if (u == v) break;
            }
            numComp++;
        }
    }

    bool solve() {
//        for (int i = 0; i < n; i++) {
//            cout << "list " << i << endl;
//            for (int u : adj[i]) cout << u << ' ';
//            cout << endl;
//        }
        for (int i = 0; i < n; i++) if (root[i] == -1) tarjan(i);
//        for (int i = 0; i < n; ++i) {
//            cerr << i << ' ' << root[i] << endl;
//        }
        for (int i = 0; i < n; i += 2) {
            if (root[i] == root[i ^ 1]) return 0;
            color[i >> 1] = (root[i] < root[i ^ 1]);
        }
        return 1;
    }
};

int getNode(int u, int v) {
    return u * 6 + v * 2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    TWOSAT f(n * 6);

    for (int i = 0; i < n; i++) {
        f.adj[getNode(i, 2)].push_back(getNode(i, 1));
        f.adj[getNode(i, 1)].push_back(getNode(i, 0));
        f.adj[getNode(i, 0) ^ 1].push_back(getNode(i, 1) ^ 1);
        f.adj[getNode(i, 1) ^ 1].push_back(getNode(i, 2) ^ 1);
    }


    for (int i = 0; i < m; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        u--, v--;
        if (c == 'x') {
            f.addEdge(getNode(u, 0) ^ 1, getNode(v, 0) ^ 1);
        } else if (c == '-') {
            f.addEdge(getNode(u, 2) ^ 1, getNode(u, 2) ^ 1);
            f.addEdge(getNode(v, 2) ^ 1, getNode(v, 2) ^ 1);
            f.addEdge(getNode(u, 0), getNode(u, 0));
            f.addEdge(getNode(v, 0), getNode(v, 0));
            f.addEdge(getNode(u, 1) ^ 1, getNode(v, 1) ^ 1);
        } else if (c == '=') {
            f.addEdge(getNode(u, 0), getNode(u, 0));
            f.addEdge(getNode(v, 0), getNode(v, 0));
            f.adj[getNode(u, 1) ^ 1].push_back(getNode(v, 2));
            f.adj[getNode(v, 1) ^ 1].push_back(getNode(u, 2));
            f.adj[getNode(u, 2)].push_back(getNode(v, 1) ^ 1);
            f.adj[getNode(v, 2)].push_back(getNode(u, 1) ^ 1);

            f.adj[getNode(u, 1)].push_back(getNode(v, 2) ^ 1);
            f.adj[getNode(v, 1)].push_back(getNode(u, 2) ^ 1);

            f.adj[getNode(u, 2) ^ 1].push_back(getNode(v, 1));
            f.adj[getNode(v, 2) ^ 1].push_back(getNode(u, 1));
        } else {
            f.addEdge(getNode(u, 1), getNode(u, 1));
            f.addEdge(getNode(v, 1), getNode(v, 1));
            f.addEdge(getNode(u, 2), getNode(v, 2));
        }
    }
    assert(f.solve());

    for (int i = 0; i < n; i++) {
        if (f.color[getNode(i, 2) >> 1]) cout << '+';
        else if (f.color[getNode(i, 1) >> 1]) cout << '=';
        else if (f.color[getNode(i, 0) >> 1]) cout << '-';
        else cout << 'x';
    }
    cout << endl;
//    for (int i = 0; i < n; i++) {
//        cout << f.color[getNode(i, 0) >> 1] << ' ' << f.color[getNode(i, 1) >> 1] << ' ' << f.color[getNode(i, 2) >> 1] << endl;
//    }
    return 0;
}