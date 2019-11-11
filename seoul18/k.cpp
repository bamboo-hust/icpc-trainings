#include <bits/stdc++.h>

using namespace std;

const int N = 11111;

struct TwoSat {
    int n;
    int numcom;
    vector<int> a[N];
    int low[N], num[N], root[N], cnt;
    vector<int> st;
    int color[N];

    TwoSat(int n): n(n) {
        memset(root, -1, sizeof root);
        memset(low, -1, sizeof low);
        memset(num, -1, sizeof num);
        memset(color, -1, sizeof color);
        cnt = 0;
        st.clear();
    }

    void add_edge(int u, int v) {
        a[u ^ 1].push_back(v);
        a[v ^ 1].push_back(u);
    }

    void tarjan(int u) {
        st.push_back(u);
        num[u] = low[u] = cnt++;
        for (int v : a[u]) {
            if (root[v] != -1) continue;
            if (low[v] == -1) tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u]) {
            while (1) {
                int v = st.back();
                st.pop_back();
                root[v] = numcom;
                if (u == v) break;
            }
            numcom++;
        }
    }

    bool solve() {
        for (int i = 0; i < n; ++i) if (root[i] == -1) tarjan(i);
        for (int i = 0; i < n; i += 2) {
            if (root[i] == root[i ^ 1]) return 0;
            color[i >> 1] = (root[i] < root[i ^ 1]);
        }
        return 1;
    }
};

int n, k;

int main() {
    ios::sync_with_stdio(false);
    cin >> k >> n;
    TwoSat G(k * 2);
    for (int i = 1; i <= n; ++i) {
        int pos[3];
        char c[3];
        for (int j = 0; j < 3; ++j) {
            cin >> pos[j] >> c[j];
            --pos[j];
        }
        for (int x = 0; x < 3; ++x) {
            for (int y = 0; y < x; ++y) {
                G.add_edge(pos[x] * 2 + (c[x] == 'B'), pos[y] * 2 + (c[y] == 'B'));
            }
        }
    }
    if (!G.solve()) {
        cout << -1 << endl;
        return 0;
    }
    //for (int i = 1; i <= k; ++i) cout << i; cout << endl;
    for (int i = 0; i < k; ++i) {
        cout << (G.color[i] ? 'R' : 'B');
    }
    cout << endl;
}