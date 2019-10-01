#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int color[N];
vector<int> a[N];

int n, m, k;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        for (int i = 1; i <= n; ++i) cin >> color[i];
        for (int i = 1; i <= m; ++i) {
            int u, v;
            cin >> u >> v;
            a[u].push_back(v);
            a[v].push_back(u);
        }

        vector< vector<int> > nodes_with_color(k + 1, vector<int>());
        for (int i = 1; i <= n; ++i) {
            nodes_with_color[color[i]].push_back(i);
        }

        int last = 0;
        for (int c = 1; c <= k; ++c) {
            for (int u : nodes_with_color[c]) {
                int max_smaller = 0;
                for (int v : a[u]) {
                    if (color[v] < color[u]) {
                        max_smaller = max(max_smaller, color[v]);
                    }
                }
                color[u] = max_smaller + 1;
                if (color[u] > color[last]) {
                    last = u;
                }
            }
        }

        cout << color[last] << ' ';
        for (int i = 1; i <= n; ++i) {
            cout << color[i] << ' ';
        }
        cout << '\n';

        for (int i = color[last]; i > 0; --i) {
            cout << last << ' ';
            for (int v : a[last]) {
                if (color[v] == color[last] - 1) {
                    last = v;
                    break;
                }
            }
        }
        cout << '\n';

        for (int i = 1; i <= n; ++i) a[i].clear();
    }
}