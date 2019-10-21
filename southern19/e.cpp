#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 1000;

int n;
string s[N];
long long res = 0;

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
} dsu;

//set last = 0 everytime we add new string
struct SuffixAutomaton {
    static const int CHARACTER = 26;
    int suf[N], nxt[N][CHARACTER], cnt, last, len[N];
    vector<int> id[N];
    int ids[N];
    int pos[N];
    vector<int> adj[N];

    SuffixAutomaton() {
        memset(suf, -1, sizeof suf);
        memset(nxt, -1, sizeof nxt);
        memset(len, 0, sizeof len);
        last = cnt = 0;
    }

    int getNode(int last, int u) {
        int q = nxt[last][u];
        if (len[last] + 1 == len[q]) {
            return q;
        }
        int clone = ++cnt;
        len[clone] = len[last] + 1;
        for (int i = 0; i < CHARACTER; i++) {
            nxt[clone][i] = nxt[q][i];
        }
        while (last != -1 && nxt[last][u] == q) {
            nxt[last][u] = clone;
            last = suf[last];
        }
        suf[clone] = suf[q];
        return suf[q] = clone;
    }

    void add(int u) {
        if (nxt[last][u] == -1) {
            int newNode = ++cnt;
            len[newNode] = len[last] + 1;
            while (last != -1 && nxt[last][u] == -1) {
                nxt[last][u] = newNode;
                last = suf[last];
            }
            if (last == -1) {
                suf[newNode] = 0;
                last = newNode;
                return;
            }
            suf[newNode] = getNode(last, u);
            last = newNode;
        } else {
            last = getNode(last, u);
        }
    }



    void build() {
        ids[0] = 0;
        for (int i =1 ; i <= cnt; i++) {
            ids[i] = i;
            adj[suf[i]].push_back(i);
        }
        sort(ids, ids + cnt + 1, [&](int u, int v) {
            return len[u] > len[v];
        });
        for (int i = 0; i <= cnt; i++) {
            int u = ids[i];
            for (int v : adj[u]) {
                for (int val : id[v]) {
                    id[u].push_back(val);
                }
            }
            int root = -1;
            for (int val : id[u]) {
                if (root == -1) {
                    root = val;
                } else {
                    int foo = dsu.unite(root, val);
                    if (foo) {
                        res += len[u];
                        root = foo;
                    }
                }
            }
            id[u].clear();
            if (root != -1) id[u].push_back(root);
        }
    }
} sa;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        sa.last = 0;
        for (char u : s[i]) {
            sa.add(u - 'a');
        }
    }
    for (int i = 1; i <= n; i++) {
        int cur = 0;
        for (char u : s[i]) {
            cur = sa.nxt[cur][u - 'a'];
            sa.id[cur].push_back(i);
        }
    }
    sa.build();
    cout << res << endl;
    return 0;
}