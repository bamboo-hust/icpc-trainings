//
// Created by lad on 9/27/19.
//

#include <bits/stdc++.h>

using namespace std;

const int N = 110;

int n;
int a[N][N];
vector<pair<int, pair<int, int>>> ls;
int root[N];
int res[N][N];

int getRoot(int u) {
    return root[u] ? root[u] = getRoot(root[u]) : u;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            if (i < j) ls.push_back(make_pair(a[i][j], make_pair(i, j)));
        }
    }
    sort(ls.begin(), ls.end());
    reverse(ls.begin(), ls.end());
    for (int l = 0, r = 0; l < ls.size(); l = r) {
        while (r < ls.size() && ls[l].first == ls[r].first) r++;
        for (int i = l; i < r; i++) {
            int u = ls[i].second.first;
            int v = ls[i].second.second;
            u = getRoot(u);
            v = getRoot(v);
            if (u == v) {
                cout << "NO\n";
                return 0;
            }
        }

        for (int i = l; i < r; i++) {
            int u = ls[i].second.first;
            int v = ls[i].second.second;
            u = getRoot(u);
            v = getRoot(v);
            if (u == v) continue;
            res[u][v] = res[v][u] = ls[i].first;
            root[u] = v;
        }
    }
    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) cout << -1 << ' ';
            else cout << res[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}