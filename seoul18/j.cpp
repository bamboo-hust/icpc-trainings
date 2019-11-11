#include <bits/stdc++.h>

using namespace std;

const int N = 1024;

bitset<N> was[N];
vector< pair<int, int> > a[N];
bool is_human[N];
bool is_military[N];
int n, num_edge, num_color, num_human, num_military;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> num_edge >> num_color >> num_human >> num_military;
    for (int i = 0; i < num_human; ++i) {
        int u; cin >> u;
        is_human[u] = true;
    }
    for (int i = 0; i < num_military; ++i) {
        int u; cin >> u;
        is_military[u] = true;
    }
    for (int i = 0; i < num_edge; ++i) {
        int u, c, v;
        cin >> u >> c >> v;
        a[v].push_back(make_pair(u, c));
    }

    queue< pair<int, int> > Q;
    for (int u = 0; u < n; ++u) if (is_military[u]) for (int v = 0; v <= u; ++v) if (is_military[v]) {
        Q.push(make_pair(u, v));
        was[u][v] = 1;
    }

    while (!Q.empty()) {
        auto u = Q.front(); Q.pop();
        for (auto x : a[u.first]) for (auto y : a[u.second]) if (x.second == y.second) {
            pair<int, int> v = make_pair(x.first, y.first);
            if (v.first < v.second) swap(v.first, v.second);
            if (was[v.first][v.second]) continue;
            was[v.first][v.second] = true;
            Q.push(v);
        }
    }

    for (int u = 0; u < n; ++u) for (int v = 0; v <= u; ++v) if (was[u][v]) {
        if ((is_human[u] && !is_human[v]) || (!is_human[u] && is_human[v])) {
            cout << "YES" << endl;
            return 0;
        }
    }

    cout << "NO" << endl;

    return 0;
}